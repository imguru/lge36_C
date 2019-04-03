#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

// 시그널 핸들러에서 절대 블록 연산을 사용하면 안된다.
// 시그널 핸들러가 반환하지 않는다면, 부모 프로세스의 코드를 수행할 수 없다.
//   wait: 블록 함수
//   waitpid: 넌블록을 지원합니다.
void on_sigchld(int signum) {
	int status;
	printf("자식 죽음..\n");
	while (waitpid(-1, &status, WNOHANG) > 0)
		;
}

#if 0
// 문제점: 시그널은 중첩될 수 없다.
//         같은 시그널이 동시에 여러개 발생하여도, 한개만 처리 가능하다.
void on_sigchld(int signum) {
	int status;
	printf("자식 죽음..\n");
	while (wait(&status) > 0)
		;
}
#endif

#if 0
void on_sigchld(int signum) {
	int status;
	printf("자식 죽음..\n");
	wait(&status);
}
#endif

int main() {
	pid_t pid;
	int i;
	int j;
	int status;

	// signal 시스템 콜을 통해서 시그널 핸들러를 등록할 수 있다.
	signal(SIGCHLD, &on_sigchld);

	for (j = 0; j < 10; ++j) {
		if (j == 5) {
			sleep(2);
		}

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
	}

	// 자식 프로세스의 종료 상태값을 얻어온다.
	// wait(&status);
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









