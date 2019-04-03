#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int status;
	pid_t pid;
	pid = fork();

	if (pid == 0) {
		sleep(100);
		exit(42);
	}

	printf("pid: %d\n", pid);

	// status: 2바이트가 유효한 데이터입니다.
	// 상위 8비트: 정상 종료 코드 값
	// 하위 8비트: 비정상 종료 코드 값
	wait(&status);
	if (WIFEXITED(status)) {
		printf("자식 프로세스가 정상 종료되었음...\n");
		printf("code: %d\n", WEXITSTATUS(status));
	} else if (WIFSIGNALED(status)) {
		printf("자식 프로세스가 시그널에 의해 종료되었음...\n");
		printf("signal: %d\n", WTERMSIG(status));

		if (WCOREDUMP(status)) {
			printf("코어 파일이 생성되었습니다..\n");
		}
	} else if (WIFSTOPPED(status)) {
		printf("멈춤...\n");
		printf("멈춤 시그널: %d\n", WSTOPSIG(status));
	}


}













