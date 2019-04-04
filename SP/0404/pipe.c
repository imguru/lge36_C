
#include <unistd.h>

#include <stdio.h>

// int pipe(int pipefd[2]);

int main() {
	int p[2];
	char buf[32];
	int len;

	pipe(p);
	printf("%d\n", p[0]);
	printf("%d\n", p[1]);

	write(p[1], "hello", 5);
	write(p[1], "hello", 5);
	getchar();

	len = read(p[0], buf, sizeof buf);
	buf[len] = 0;
	printf("buf: %s\n", buf);
}










