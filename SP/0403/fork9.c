#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

void on_sigchld(int signum) {
	int status;
	printf("자식 죽음..\n");
	while (waitpid(-1, &status, WNOHANG) > 0)
		;
}

int main() {
	pid_t pid;
	int i;
	int j;
	int status;

	// signal 시스템 콜을 통해서 시그널 핸들러를 등록할 수 있다.
	signal(SIGCHLD, &on_sigchld);

	for (j = 0; j < 10; ++j) {
		pid = fork();
		if (pid == 0) {
			for (i = 0; i < 30; ++i) {
				sleep(1);
				printf("\t\tchild\n");
			}
			exit(3);
		} else if (pid == -1) {
			perror("fork");
			exit(1);
		}
	}

	while (1) {
		sleep(1);
		printf("parent\n");
	}

	return 0;
}









