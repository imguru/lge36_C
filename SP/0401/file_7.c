#include <unistd.h> // usleep, sleep
#include <stdio.h>

int main() {
	FILE *fp;
	char buf[32];
	
	fp = fopen("file.c", "r");
	if (fp == NULL) {
		fprintf(stderr, "file open error.\n");
		return 1;
	}

	while ( fgets(buf, sizeof buf, fp) != NULL ) {
		usleep(1000 * 100);  // 100ms
		fputs(buf, stdout);
		fflush(stdout);
	}

	fclose(fp);
	return 0;
}
