#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

// open: O_CLOEXEC
// fcntl: FD_CLOEXEC
int main() {
	// int fd = open("a.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	int fd = open("a.txt", O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0644);

	execlp("./test", "./test", NULL);
}
