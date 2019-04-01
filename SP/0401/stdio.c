
#include <stdio.h>

// stdout(FILE *)
// stdin(FILE *)
//   => 라인 버퍼링을 합니다.

// stderr(FILE *)
//   => 버퍼링을 하지 않습니다.

int main() {
	// printf("hello");
	// fflush(stdout);
	fprintf(stderr, "hello");

	while (1)
		;
}
