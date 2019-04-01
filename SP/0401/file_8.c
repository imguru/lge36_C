#include <unistd.h> // usleep, sleep
#include <stdio.h>

int main() {
	FILE *fp;
	char buf[128];
	int ret;
	
	fp = fopen("file.c", "r");
	if (fp == NULL) {
		fprintf(stderr, "file open error.\n");
		return 1;
	}

	// 읽은 바이트 수 만큼 출력을 하기 위해서 반환값이 필요하다.
	while ( ret = fread(buf, 1, sizeof buf, fp) ) {
		usleep(1000 * 100);  // 100ms
		fwrite(buf, 1, ret, stdout);
		fflush(stdout);
	}

	fclose(fp);
	return 0;
}
