#include <stdio.h>
#include <pthread.h>

// $ gcc lock.c -pthread
pthread_mutex_t mutex; // = PTHREAD_MUTEX_INITIALIZER;

int main()
{
	pthread_mutex_init( &mutex , 0 );

	pthread_mutex_lock( &mutex );
	printf("임계영역 진입\n");
	pthread_mutex_unlock( &mutex );
	pthread_mutex_unlock( &mutex );
	return 0;
}

