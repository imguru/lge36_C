#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>

// Packet
// temp(4):cds(4)
// TCP는 데이터의 경계가 존재하지 않으므로, 데이터를 보내기 전에,
// 길이를 보내야 한다.

int main() {
	int csock = socket(PF_INET, SOCK_STREAM, 0);
	if (csock == -1) {
		perror("socket");
		return 1;
	}

	struct sockaddr_in saddr = {0, };
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	saddr.sin_port = htons(5000);

	if (connect(csock, (struct sockaddr *)&saddr, sizeof saddr) == -1) {
		perror("connect");
		return 1;
	}

	printf("연결이 시작되었습니다...\n");
	char buf[64];
	int ret;

	// buf
	//   len(2):temp(4):cds(4)
	int i, j;
	short len;
	for (i = 0; i < 100; ++i) {
		int cds = 42;
		int temp = 100;

		char *p = buf;
		*(int *)p = htonl(temp);
		p += sizeof(int);

		*(int *)p = htonl(cds);
		p += sizeof(int);

		len = htons(p - buf);

		write(csock, &len, sizeof len);
		write(csock, buf, p - buf);
#if 0
		for (j = 0; j < p-buf; ++j) {
			write(csock, buf + j, 1);
			usleep(10);
		}
#endif
	}
	
	close(csock);
	return 0;
}





