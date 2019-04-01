#include <stdio.h>

// 파일을 문자열을 쓰고, 그 문자열을 파일로부터 다시 읽어오는 코드.

// "r": 파일이 존재하지 않으면, 실패한다.
// "w": 파일이 존재하지 않으면, 생성하고,
//      파일이 존재하면, 파일의 크기를 0으로 만든다.

// hello.txt - FILE(offset: 2)
// 표준 입출력의 FILE 구조체 내부의 offset을 조정하는 함수
// int fseek(FILE *stream, long offset, int whence);
//   offset: whence를 기준으로 얼마만큼 더할지를 결정하는 값.
//   whence
//    1) SEEK_SET: 시작
//    2) SEEK_END: 끝
//    3) SEEK_CUR: 현재
int main() {
	int ret;
	char buf[32];
	FILE *fp = fopen("hello.txt", "w+");

	ret = fwrite("he", 1, 2, fp);
	printf("ret: %d\n", ret);

	getchar();
	// fseek(fp, 0, SEEK_SET); // offset = 0
	// rewind(fp);
	fseek(fp, -ret, SEEK_CUR);

	fread(buf, 1, ret, fp);
	printf("buf: %s\n", buf);
}














