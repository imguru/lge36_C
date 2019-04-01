#include <stdio.h>

// fopen을 하면 FILE 구조체가 무조건 생성됩니다.
// wfp -> FILE(offset=0) -> "hello.txt"
// rfp -> FILE(offset=0) -> "hello.txt"

int main() {
	int ret;
	char buf[32];
	FILE *wfp = fopen("hello.txt", "w");  
	FILE *rfp = fopen("hello.txt", "r");

	ret = fwrite("he", 1, 2, wfp); // wfp -> FILE(offset=2)
	fflush(wfp); // 버퍼링 때문...

	getchar();
	fread(buf, 1, ret, rfp);       // rfp -> FILE(offset=2)

	printf("buf: %s\n", buf);
}
