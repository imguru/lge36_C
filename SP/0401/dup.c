#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>

int main() {
	int fd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

	close(1);
	dup(fd);
	// struct file*
	//  [0][ ][2][3]
	//      |     |
	//       -> [struct file]

	printf("hello, world\n");
	printf("hello, world\n");
	printf("hello, world\n");
	printf("hello, world\n");
	printf("hello, world\n");
}
