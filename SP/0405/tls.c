#include <stdio.h>
#include <string.h>
#include <pthread.h>

void foo() {
	static __thread int n;
	printf("foo: %d\n", ++n);
}

void *handler(void *arg) {
	foo();
	foo();
	foo();
}

int main() {
	int i;
	pthread_t thread[2];
	pthread_create(&thread[0], NULL, handler, NULL);
	pthread_create(&thread[1], NULL, handler, NULL);

	for (i = 0; i < 2; ++i) 
		pthread_join(thread[i], NULL);
}
