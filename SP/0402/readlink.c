
#include <stdio.h>
#include <unistd.h>

int main() {
	char buf[128];

	readlink("my_ls", buf, sizeof buf);
	// printf("buf: %s\n", buf);
	printf("%s -> %s\n", "my_ls", buf);
}
