#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>


int main() {
	int status;
	pid_t pid;
	pid = fork();

	if (pid == 0) {
		while (1)
			;
		exit(42);
	}

	printf("pid: %d\n", pid);

	// status: 2바이트가 유효한 데이터입니다.
	// 상위 8비트: 정상 종료 코드 값
	// 하위 8비트: 비정상 종료 코드 값
	wait(&status);
	printf("status: %d\n", (status >> 8) & 0xff);
	// printf("kill: %d\n", status & 0xff);
	printf("kill: %d\n", status & 0x7f);  // 시그널 번호
}













