#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>

int main() {
	int fd = open("out.txt", O_RDONLY);
	char buf[32];
	
	// dup을 사용하면 안됩니다.
	// close(0);
	// dup(fd);
	
	dup2(fd, 0);
	

	while (scanf("%s", buf) == 1) {
		printf("%s\n", buf);
	}
}
