
// fork()
//   : 새로운 프로세스를 생성하는 시스템 콜

#include <unistd.h>

#include <stdio.h>

int main() {
	fork();
	printf("hello\n");  // 이제 두 개의 프로세스가 존재합니다.
						// 부모 프로세스: 원래의 프로세스
						// 자식 프로세스: fork()에 의해서 생성된 프로세스

	return 0;
}
