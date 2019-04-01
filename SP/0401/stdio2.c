
// 일반적인 파일은 풀 버퍼링을 합니다.
// => 파일 버퍼가 가득 차면 내보냅니다.
#include <stdio.h>

// 일반 파일이 flush 되는 방법
// 1. fflush(fp);
// 2. 버퍼가 가득 차거나
// 3. fclose(fp);
int main() {
	FILE *fp = fopen("a.txt", "w");
	if (fp == NULL) {
		fprintf(stderr, "file open error.\n");
		return 1;
	}

	fprintf(fp, "hello, world..\n");
	fflush(fp);
	getchar();

	fclose(fp);
	return 0;
}
