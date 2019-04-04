
// pthread_create()
// pthread_join()

// $ gcc thread1.c -lpthread
//                  libpthread.so
// $ gcc thread1.c -pthread

#include <pthread.h>
#include <stdio.h>

#if 0
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
		void *(*start_routine) (void *), void *arg);
#endif

// thread_routine
void *thread_routine(void *arg) {
	printf("thread_routine - %s\n", (char *)arg);
	return 0;
}

// 1. 프로세스가 종료하면, 프로세스 내의 모든 스레드도 종료한다.
// 2. main 함수가 반환하면, 프로세스가 종료한다.
// 3. 프로세스 내의 모든 스레드가 종료하면, 프로세스는 종료한다.
int main() {
	pthread_t thread;
	pthread_create(&thread, NULL, thread_routine, "hello");

	// 지정된 스레드가 종료할 때까지 대기한다. - wait
	pthread_join(thread, NULL);
}













