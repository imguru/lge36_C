
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// 모든 프로세스는 주소 공간이 분리되어 있다.
//  => 데이터를 공유하기 위해서는 IPC가 필요하다.

// 부모 프로세스와 자식 프로세스의 데이터는 공유되지 않는다.
//  => 전역 변수, 지역 변수, 힙 변수

int global = 10;
int main() {
	pid_t pid;
	int stack = 5;

	pid = fork();
	if (pid == 0) {
		sleep(3);
		printf("child global: %d stack:%d\n", global, stack);

	} else if (pid > 0) {
		++global;
		--stack;
		printf("parent global: %d stack:%d\n", global, stack);

	} else {
		// printf("error...\n");
		perror("fork");
		exit(1);
	}
	

}
