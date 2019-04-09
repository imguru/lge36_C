#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

pthread_key_t key;
void foo(void){
	int *tsd;
	tsd = pthread_getspecific( key );
	if( tsd == 0 )    {
		tsd = calloc( 1, sizeof(int) );
		pthread_setspecific( key, tsd );
	}
	++*tsd;
	printf("*tsd=%d\n", *tsd );
}

void * my_handler2(void* data ){
	foo();
	foo();
	foo();
	foo();
}

// TLS를 파괴하는 시점에 호출되는 함수 - pthread_key_delete
void destr_function (void *p){
	free(p);
}

int main(){
	pthread_t tid1, tid2;
	pthread_key_create( &key, destr_function );
	pthread_create(&tid1, 0, my_handler2, 0);
	pthread_create(&tid2, 0, my_handler2, 0);
	pthread_join( tid1, 0 );
	pthread_join( tid2, 0 );
	pthread_key_delete(key);
	return 0;
}

