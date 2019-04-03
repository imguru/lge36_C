
// # ps -ef
// root      6772  6771  0 11:24 pts/0    00:00:00 [a.out] <defunct>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	pid_t pid;
	int i;
	int status;

	pid = fork();
	if (pid == 0) {
		for (i = 0; i < 3; ++i) {
			sleep(1);
			printf("\t\tchild\n");
		}
		exit(3);
	} else if (pid == -1) {
		perror("fork");
		exit(1);
	}

	// 자식 프로세스의 종료 상태값을 얻어온다.
	wait(&status);
	// 문제점: 자식 프로세스가 종료할 때까지 대기한다.
	//  => 병행성(동시성)이 제대로 구현되지 못했다.
	//  해결방법: 자식의 종료를 비동기적으로 처리할 수 있어야 한다.
	//       자식 프로세스가 종료한 경우, 부모 프로세스에게 SIGCHLD를 전달한다.

	while (1) {
		sleep(1);
		printf("parent\n");
	}

	return 0;
}









