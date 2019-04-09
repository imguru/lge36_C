#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>

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
	while ((ret = read(0, buf, sizeof buf)) > 0) {
		write(csock, buf, ret);

		ret = read(csock, buf, sizeof buf);
		if (ret == 0) {
			printf("연결이 종료되었습니다.\n");
			break;
		} else if (ret == -1) {
			perror("read");
			break;
		}

		write(1, buf, ret);
	}

	close(csock);
	return 0;
}
