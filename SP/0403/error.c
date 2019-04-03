#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <string.h>
#include <errno.h> // errno

// 1. 시스템 콜이 실패할 경우, errno 값을 통해 오류의 원인을 제공합니다.
int main() {
	int fd = open("a.txt", O_RDONLY);
	if (fd == -1) {
		// printf("errno: %d\n", errno);
		// printf("%s\n", strerror(errno));
		perror("open");
		return 1;
	}
}


#if 0
int main() {
	FILE *fp = fopen("a.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "file open error...\n");
		return 1;
	}
}
#endif
