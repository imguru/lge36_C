
#include <stdio.h>

// $ ./a.out 1.c 2.c
int main(int argc, char *argv[]) {
	FILE *src, *dest;
	char buf[128];
	int ret;

	if (argc != 3) {
		fprintf(stderr, "Usage: ...\n");
		return 1;
	}

	src = fopen(argv[1], "r");
	if (src == NULL) {
		fprintf(stderr, "file open error...%s\n", argv[1]);
		return 1;
	}

	dest = fopen(argv[2], "w");
	//                     O_WRONLY | O_TRUNC | O_CREAT, 0666

	if (dest == NULL) {
		fprintf(stderr, "file open error...%s\n", argv[2]);
		return 1;
	}
	
	while ( ret = fread(buf, 1, sizeof buf, src) ) {
		fwrite(buf, 1, ret, dest);
	}

	fclose(src);
	fclose(dest);

	return 0;
}












