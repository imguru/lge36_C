
// fork(): 부모와 자식이 동시에 코드를 수행(실행)하기 위해서 사용한다.

// 자식 프로세스는 자신이 사용하던 자원을 바로 반납하지 않는다.
// => 부모에게 자신의 종료 상태값을 주어야 자원을 해지하는 것이 가능하다.

// 자식 프로세스가 종료되었지만, 아직 종료 상태값을 전달하기 전의 자식 프로세스// => 좀비 프로세스
//  : 부모 프로세스가 wait 시스템 콜을 통해 자식 프로세스의 종료 상태값을 얻어올 수 있다.

// # ps -ef
// root      6772  6771  0 11:24 pts/0    00:00:00 [a.out] <defunct>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	pid_t pid;
	int i;

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

	while (1) {
		sleep(1);
		printf("parent\n");
	}

	return 0;
}









