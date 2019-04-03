
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// 동시성 프로그래밍(Concurrent Programming)
//  1. Multi Process
//  2. Multi Thread

// fork()의 반환값을 통해서 부모 프로세스와 자식 프로세스를 분기하는 방법

// 부모 프로세스의 반환값: 자식의 pid
// 자식 프로세스의 반환값: 0
// 실패: -1
int main() {
	pid_t pid;
	int i;

	pid = fork();
	if (pid > 0) {
		printf("부모 프로세스...\n");
		for (i = 0; i < 10; ++i) {
			printf("부모: %d\n", i + 1);
			sleep(1);
		}
		exit(0);
	} else if (pid == 0) {
		printf("자식 프로세스...\n");
		for (i = 0; i < 10; ++i) {
			printf("자식: %d\n", 10 - i);
			sleep(1);
		}
		exit(0);
	}
}











