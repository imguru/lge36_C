#include <stdio.h>

long get_fsize(FILE *fp) {
	long ret;
	long origin;

	// 1. 현재의 파일 오프셋 위치를 백업한다.
	origin = ftell(fp);

	// 2. 파일의 사이즈를 구한다.
	fseek(fp, 0, SEEK_END);
	ret = ftell(fp);

	// 3. 파일의 오프셋을 복원한다.
	fseek(fp, origin, SEEK_SET);

	return ret;
}


int main(int argc, char **argv) {
	FILE *fp;
	long size;

	if (argc != 2) {
		return 1;
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		return 1;
	}

	size = get_fsize(fp);
	printf("filesize: %ld\n", size);

}
