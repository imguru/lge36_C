#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <stdio.h>

int main() {
	int ret;
	char buf[32];
	// FILE *wfp = fopen("hello.txt", "w");  
	// int wfd = open("hello.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// umask(0);
	int wfd = open("hello.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	// 0644
	// 110100100
	// rw-r--r--

	// FILE *rfp = fopen("hello.txt", "r");
	int rfd = open("hello.txt", O_RDONLY);

	// ret = fwrite("he", 1, 2, wfp); // wfp -> FILE(offset=2)
	// fflush(wfp); // 버퍼링 때문...
	write(wfd, "he", 2);

	getchar();

	ret = read(rfd, buf, sizeof buf);
	buf[ret] = '\0';

	printf("buf: %s\n", buf);
}
