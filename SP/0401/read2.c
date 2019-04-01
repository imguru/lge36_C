

// open -> struct file 구조체 생성된다.
//  같은 파일을 open을 두번 하면, 오프셋을 별도로 관리할 수 있다.

#include <stdio.h>

int main() {
	int fd1 = open("hello.txt", O_RDONLY);
	int fd2 = open("hello.txt", O_RDONLY);

	char buf1[32];
	char buf2[32];

	read(fd1, buf1, 2);
	buf1[2] = '\0';
	printf("buf1: %s\n", buf1);

	read(fd2, buf2, 2);
	buf2[2] = '\0';
	printf("buf2: %s\n", buf2);
}








