#include <unistd.h> // usleep, sleep
#include <stdio.h>

int main() {
	FILE *fp;
	int ch;
	
	fp = fopen("file.c", "r");
	if (fp == NULL) {
		fprintf(stderr, "file open error.\n");
		return 1;
	}

	while ( (ch = fgetc(fp)) != EOF ) {
		usleep(1000 * 100);  // 100ms
		fputc(ch, stdout);
		fflush(stdout);
	}

	fclose(fp);
	return 0;
}
