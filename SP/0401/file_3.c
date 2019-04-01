#include <stdio.h>

// C 언어 char 타입은 3개입니다.
// char => 문자를 표현하기 위한 타입이다.
//  => signed / unsigned 에 대해서 정의되어 있지 않습니다.

// signed char   => 부호 있는 1바이트 정수
// unsigned char => 부호 없는 1바이트 정수

// # ./a.out  file.c
//    argv[0] argv[1]
//    argc=2
int main(int argc, char *argv[]) {
	FILE *fp;
	int ch;
	// char ch;
	// !!!
	int count = 0; // ++count

	if (argc != 2) {
		printf("Usage: ./a.out <filename>\n");
		return 1;
	}

	fp = fopen(argv[1], "r");
	// 리눅스는 아스키와 바이너리를 동일하게 취급한다.
	if (fp == NULL) {
		printf("file open error...\n");
		return 1;
	}

	// fgetc 함수는 파일의 끝에 도달하면 EOF를 반환한다.
	// #define EOF -1
	// 0xff == 0xffffffff
	// char 타입으로 처리하면,
	// - 0xff의 데이터와 EOF를 같다고 처리한다.
	// int 타입으로 처리하면
	// - 0x000000ff == 0xffffffff
	while ((ch = fgetc(fp)) != EOF) {
		// fputc(ch, stdout);
		++count;
	}

	printf("count: %d\n", count);

	fclose(fp);
	return 0;
}













