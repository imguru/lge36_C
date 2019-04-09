#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

// 재진입 불가능 함수
//  : 함수가 상태를 유지한다.
//   => 함수가 내부에 정적 변수와 전역 변수를 사용하고 있다.

// 해결 방법
// 1) 상태를 caller가 저장한다. - linux
//    : strtok_r

// 2) TLS(Thread Local Storage) / TSS(Thread Specific Storage)
//   : 스레드마다 고유한 데이터
//   - 정적 TLS
//   - 동적 TLS(Thread API)

char *strtok(char *str, const char *delim) {
	static char* ptr;
	return strtok_r(str, delim, &ptr);
}

void * my_handler1(void* data ){
	char hp[] = "010-1234-5678";
	char *p;
	char *ptr;

	p = strtok_r( hp, "-", &ptr);
	while(p)    {
		printf("[%s]\n", p );
		usleep(100);
		p = strtok_r( 0, "-", &ptr);
	}
}
void * my_handler2(void* data ){
	char ip[] = "192.168.100.128";
	char *p;
	char *ptr;
	p = strtok_r( ip, ".", &ptr);
	while(p)
	{
		printf("[%s]\n", p );
		usleep(100);
		p = strtok_r( 0, ".", &ptr);
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


