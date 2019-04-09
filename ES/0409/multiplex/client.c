#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>

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

	struct pollfd fds[2];
	fds[0].fd = 0;
	fds[0].events = POLLIN;

	fds[1].fd = csock;
	fds[1].events = POLLIN;

	printf("연결이 시작되었습니다...\n");
	char buf[64];
	int ret;
	while (1) {
		if (poll(fds, 2, -1) == 0)
			continue;

		if (fds[0].revents & POLLIN) {
			ret = read(0, buf, sizeof buf);
			if (ret <= 0) break;

			write(csock, buf, ret);
		}

		if (fds[1].revents & POLLIN) {
			ret = read(csock, buf, sizeof buf);
			if (ret <= 0) break;

			write(1, buf, ret);
		}
	}

	close(csock);
	return 0;
}
