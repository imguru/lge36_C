#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

void *thread_routine(void *arg) {
	int i;

	for (i = 0; i < 10; ++i) {
		printf("thread_routine - %s\n", (char *)arg);
		sleep(1);
	}

	return 0;
}

int main() {
	int i;
	pthread_t thread;
	pthread_create(&thread, NULL, thread_routine, "hello");
	
	for (i = 0; i < 10; ++i) {
		printf("main - %d\n", i);
		sleep(1);
	}

	pthread_join(thread, NULL);
}













