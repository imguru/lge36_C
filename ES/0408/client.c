// 1. socket()
// 2. connect()
#include <unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>

int main() {
	int csock = socket(PF_INET, SOCK_STREAM, 0);
	if (csock == -1) {
		perror("socket()");
		return -1;
	}
	
	struct sockaddr_in saddr = {0, };
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	saddr.sin_port = htons(5000);

		// "192.168.56.100" or "127.0.0.1" or "192.168.137.100"
		// 빅 엔디안 32비트로 변환해서 저장해야 한다.
		//  => inet_addr
		//    in_addr_t(== __be32)
	int ret = connect(csock, (struct sockaddr *)&saddr, sizeof saddr);
	if (ret == -1) {
		perror("connect");
		return -1;
	}
	printf("서버와의 접속이 성립되었습니다...\n");

	char buf[128];
	while ((ret = read(0, buf, sizeof buf)) > 0) {
		write(csock, buf, ret);

		ret = read(csock, buf, sizeof buf);
		if (ret == 0) {
			printf("연결이 종료되었습니다...\n");
			break;
		} else if (ret == -1) {
			perror("read");
			break;
		}

		buf[ret] = '\0';
		printf("%s\n", buf);
	}

	close(csock);
}




















