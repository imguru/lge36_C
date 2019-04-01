#include <stdio.h>
#include <string.h>

// merge: 여러 개의 파일을 하나의 파일로 합치는 프로그램
// a.c(10) b.c(20) c.c(30)
//  => a.merge(각 파일의 정보를 저장해야 한다.)
//             : 파일 이름 / 크기

typedef struct {
	char fname[20];
	long fsize;
} INFO;

long get_fsize(FILE *fp) {
	long ret;
	long origin;

	origin = ftell(fp);
	fseek(fp, 0, SEEK_END);
	ret = ftell(fp);
	fseek(fp, origin, SEEK_SET);

	return ret;
}

// ./a.out a.c b.c c.c merge.out
//  argv[0] 1   2   3   4
//  argc=5

int main(int argc, char **argv) {
	int ret;
	int i;
	INFO info;
	FILE *src, *dest;
	char buf[512];

	dest = fopen(argv[argc - 1], "w");
	for (i = 0; i < argc - 2; i++) {

		src = fopen( argv[i+1], "r");

		strcpy(info.fname, argv[i+1]); // fname 저장
		info.fsize = get_fsize(src);   // fsize 저장

		fwrite(&info, 1, sizeof info, dest);
		while ( ret = fread(buf, 1, sizeof buf, src) ) {
			fwrite(buf, 1, ret, dest);
		}
		fclose(src);
	}

	fclose(dest);
}



































