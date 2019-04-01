
#include <stdio.h>
#include <fcntl.h>

int main() {
	close(1);
	int fd = open("a.txt", O_WRONLY | O_CREAT);

	printf("hello, world...\n");
}
