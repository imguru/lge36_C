
#include <pthread.h>

#include <stdio.h>

// 아래의 코드는 -O2 옵션을 사용하면, 제대로 종료하지 않습니다.
// 아래의 코드는 '메모리 가시성 문제' 라고 부릅니다.
// => 컴파일러가 최적화한 변수가, 레지스터에 존재하여, 메모리에서 값이 변경되더라도 관찰하지 못하는 문제.

// 반드시 메모리로부터 읽거나 쓰도록 변수를 한정해야 합니다.
// volatile

void *foo(void *arg) {
	volatile int* pn = (int *)arg;

	while (*pn)
		;

	return 0;
}

int main() {
	int n = 1;

	pthread_t thread;
	pthread_create(&thread, NULL, foo, &n);
	getchar();

	n = n - 1;
	pthread_join(thread, NULL);

	return 0;
}
