
// fseek
// ftell
//   => 현재의 offset을 확인하는 함수입니다.

// => 파일의 크기를 쉽게 구할 수 있습니다.
// => fseek을 통해 파일의 마지막 위치로 이동합니다.
//    그시점의 offset 값이 파일의 크기입니다.

#include <stdio.h>

int main(int argc, char **argv) {
	char buf[32];
	FILE *fp;
	long filesize;
	if (argc != 2) {
		fprintf(stderr, "Usage: ./a.out <filename>\n");
		return 1;
	}

	fp = fopen(argv[1], "r");
	//------
	fseek(fp, 0, SEEK_END);  // 1. 파일의 마지막 위치로 이동.
	filesize = ftell(fp);    // 2. 그 위치의 오프셋 값이 파일의 크기입니다.
	//------

	rewind(fp);
	// = fseek(fp, 0, SEEK_SET);
	fread(buf, 1, sizeof buf, fp);


	printf("file size: %ld\n", filesize);
	fclose(fp);
	return 0;
}







