#include <stdio.h>
#include <pthread.h>

// mutex
//  => 재귀 락(RECURSIVE_LOCK)
pthread_mutex_t mutex;
pthread_mutexattr_t attr;

void foo(int i)
{
	if(i==0)
		return;
	pthread_mutex_lock( &mutex );
	printf("임계영역 진입\n");
	foo(i-1);
	pthread_mutex_unlock( &mutex );
}

int main()
{	
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init( &mutex , &attr );

	foo(10);

	return 0;
}






