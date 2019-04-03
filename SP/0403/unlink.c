#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>

int main() {
	int fd;
	int ret;
	char buf[128];

	fd = open("zzz", O_RDWR | O_CREAT | O_TRUNC, 0644);
	getchar();

	unlink("zzz"); // 파일의 이름이 지워진다.
	getchar();

	write(fd, "hello", 5);
	getchar();

	// 표준 라이브러리 FILE 구조체의 오프셋을 변경: fseek
	// 커널 내의 struct file 구조체의 오프셋을 변경: lseek
	lseek(fd, 0, SEEK_SET);

	ret = read(fd, buf, sizeof buf);
	buf[ret] = '\0';
	printf("%s\n", buf);
	getchar();

	close(fd);

	getchar();
}

















