
#include <pthread.h>
#include <stdio.h>

#define MAX_THREAD 2

// 경쟁 조건(Race condition)
//  : 두 개 이상의 스레드가 동일한 메모리에 데이터를 변경하거나 읽는 현상.
//  local = local + 1
//  sum = local;
//  (공유 변수)
//  => 공유 변수의 값을 변경하는 연산은 원자적(Atomic)이지 않다.

// 임계 영역(Critical Section)
//  : 두 개이상의 스레드에 의해 접근되는 공유변수에 대한 코드 영역

// 상호 배제(Mutual Exclusion)
//  : 공유 변수에 접근하는 임계 영역에 대해서 오직 한개의 스레드만 접근
//    하도록 제어하는 것.


// int lock = 0;


int sum = 0;
#if 0
void *foo(void *arg) {
	int i;

	for (i = 0; i < 100000000 / MAX_THREAD; i++) {
#if 0
		while (lock)
			;
		lock = 1;
#endif
		++sum;
#if 0
		lock = 0;
#endif
	}
	return 0;
}
#endif

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// lock = 0;

void *foo(void *arg) {
	int i;

	for (i = 0; i < 100000000 / MAX_THREAD; i++) {
		//----
		pthread_mutex_lock(&mutex);   // while(lock);  lock = 1
		++sum;
		pthread_mutex_unlock(&mutex); // lock = 0;
		//----
	}
	return 0;
}

int main() {
	pthread_t thread_id[MAX_THREAD];
	int status, i;

	for (i = 0; i < MAX_THREAD; ++i) {
		status = pthread_create(&thread_id[i], 0, foo, 0);
	}

	for (i = 0; i < MAX_THREAD; ++i) {
		status = pthread_join(thread_id[i], 0);
	}

	printf("sum = %d\n", sum);
	return 0;
}









