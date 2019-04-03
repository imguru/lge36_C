#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
	int fd = open("a.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

	close(1);
	dup(fd);

	execlp("ls", "ls", "-l", NULL);
}
