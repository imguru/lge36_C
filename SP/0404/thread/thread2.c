#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

void *thread_routine(void *arg) {
	int i;

	for (i = 0; i < 10; ++i) {
		printf("thread_routine - %s\n", (char *)arg);
		sleep(1);
	}

	return (void*)0x42;
}

int main() {
	int i;
	void *ret;
	pthread_t thread;
	pthread_create(&thread, NULL, thread_routine, "hello");

	// 호출한 스레드를 종료한다.
	pthread_exit(0);
	

#if 0
	for (i = 0; i < 10; ++i) {
		printf("main - %d\n", i);
		sleep(1);
	}
#endif

	// pthread_join(thread, NULL);
	// pthread_join(thread, &ret);
	// printf("ret: %p\n", ret);
}













