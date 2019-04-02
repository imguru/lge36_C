#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

//                                argc-1
//            argv 1       2         3
// $ ./a.out hello.txt world.txt show.txt
int main(int argc, char* argv[]) {
	char buf[512];
	int i;
	int ret;
	int fd[1024];

	for (i = 0; i < argc - 1; ++i) {
		fd[i] = open(argv[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}

	while ((ret = read(0, buf, sizeof buf)) > 0) {
		write(1, buf, ret);
		for (i = 0; i < argc - 1; ++i) {
			write(fd[i], buf, ret);
		}
	}

	for (i = 0; i < argc - 1; ++i) {
		close(fd[i]);
	}

	return 0;
}

