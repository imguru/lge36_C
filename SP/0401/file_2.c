#include <stdio.h>

int main() {
	FILE *fp;
	char ch;
	int count = 0; // ++count

	fp = fopen("file.c", "r");
	// 리눅스는 아스키와 바이너리를 동일하게 취급한다.
	if (fp == NULL) {
		printf("file open error...\n");
		return 1;
	}

	// fgetc 함수는 파일의 끝에 도달하면 EOF를 반환한다.
	// #define EOF -1
	while ((ch = fgetc(fp)) != EOF) {
		// fputc(ch, stdout);
		++count;
	}

	printf("count: %d\n", count);

	fclose(fp);
	return 0;
}













