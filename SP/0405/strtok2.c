#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

char *xstrtok(char *str, const char *delim) {
	static __thread char* ptr;
	return strtok_r(str, delim, &ptr);
}

void * my_handler1(void* data ){
	char hp[] = "010-1234-5678";
	char *p;

	p = xstrtok( hp, "-");
	while(p)    {
		printf("[%s]\n", p );
		usleep(100);
		p = xstrtok( 0, "-");
	}
}
void * my_handler2(void* data ){
	char ip[] = "192.168.100.128";
	char *p;
	p = xstrtok( ip, ".");
	while(p)
	{
		printf("[%s]\n", p );
		usleep(100);
		p = xstrtok( 0, ".");
	}
}

int main()
{
	pthread_t tid1, tid2;

	pthread_create(&tid1, 0, my_handler1, 0);
	pthread_create(&tid2, 0, my_handler2, 0);
	pthread_join( tid1, 0 );
	pthread_join( tid2, 0 );
	return 0;
}


