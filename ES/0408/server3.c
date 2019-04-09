#include <unistd.h>

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>

#include <stdio.h>

int main() {
	int ssock = socket(PF_INET, SOCK_STREAM, 0);
	if (ssock == -1) {
		perror("socket()");
		return -1;
	}

	int option = 1;
	setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof option);

	struct sockaddr_in saddr = {0, };
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = INADDR_ANY;
	saddr.sin_port = htons(5000);
	if (bind(ssock, (struct sockaddr *)&saddr, sizeof saddr) == -1) {
		perror("bind");
		return -1;
	}

	listen(ssock, SOMAXCONN);
	struct sockaddr_in caddr = {0, };
	socklen_t socklen = sizeof caddr;

	while (1) {
		int csock = accept(ssock, (struct sockaddr *)&caddr, &socklen);
		printf("csock: %d\n", csock);

		char buf[128];
		while (1) {
			int ret = read(csock, buf, sizeof buf);
			if (ret == 0) {
				printf("연결이 종료되었습니다.\n");
				break;
			} else if (ret == -1) {
				perror("read");
				break;
			} else {
				write(csock, buf, ret);
			}
		}
		close(csock);
	}


	close(ssock);
}




























