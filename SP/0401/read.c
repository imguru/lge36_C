#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>

int main() {
	// 2, K
	int fd = open("hello.txt", O_RDONLY);
	int ret;
	char buf[32];

	if (fd == -1) {
		fprintf(stderr, "file open error...\n");
		return 1;
	}

	// FILE 구조체는 offset을 직접 관리하고 하지만,
	// 시스템 콜은 커널 내부의 struct file 구조체에 오프셋 정보가
	// 존재한다.
	ret = read(fd, buf, 2);  // f_pos = 2
	buf[ret] = '\0';
	printf("%s\n", buf);

	ret = read(fd, buf, 2);  // f_pos = 4
	buf[ret] = '\0';
	printf("%s\n", buf);

	close(fd);
	return 0;
}
