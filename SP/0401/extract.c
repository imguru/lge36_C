
#include <stdio.h>
#include <string.h>

// $ ./a.out merge.out

typedef struct {
	char fname[20];
	long fsize;
} INFO;

int main(int argc, char **argv) {
	INFO info;
	int ret;
	FILE *src, *dest;
	int len;
	char buff[512];
	
	src = fopen(argv[1], "r");

	while ( ret = fread(&info, 1, sizeof info, src) ) {
		printf("filename: %s, size: %ld\n", info.fname, info.fsize);

		dest = fopen(info.fname, "w");
		while ( info.fsize > 0 ) {
			len = (sizeof buff < info.fsize) ? sizeof buff : info.fsize;

			ret = fread(buff, 1, len, src);
			fwrite( buff, 1, ret, dest);

			info.fsize -= ret;
		}
		fclose(dest);
	}
	fclose(src);

	return 0;
}

