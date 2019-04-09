#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <poll.h>

// read
//   : 파일 디스크립터의 수신 버퍼에 데이터가 존재하지 않으면
//     블록된다.

// read를 두 개의 디스크립터에 대해서 수행할 경우, 연속적으로 처리할 수 없다.

int main() {
	int fd = open("myfifo", O_RDWR);
	char buf[128];
	int ret;

	struct pollfd fds[2];
	fds[0].fd = 0;
	fds[0].events = POLLIN;

	fds[1].fd = fd;
	fds[1].events = POLLIN;
	
	while (1) {
		if (poll(fds, 2, -1) == 0)
			continue;

		if (fds[0].revents & POLLIN) {
			ret = read(0, buf, sizeof buf);
			buf[ret] = '\0';
			printf("keyboard: %s\n", buf);
		}
		if (fds[1].revents & POLLIN) {
			ret = read(fd, buf, sizeof buf);
			buf[ret] = '\0';
			printf("pipe: %s\n", buf);
		}
	}
}

















