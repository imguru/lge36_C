#include <stdio.h>
// $ ./a.out hello world show
//      $0    $1    $2    $3

// argc: 인자의 개수
// argv
//   [0] -> "./a.out"
//   [1] -> "hello"
//   [2] -> "world"
//   [3] -> "show"
void foo(char *s) {
	printf("%s\n" ,s);
}

int add(int a, int b) {
	return a + b;
}

int main(int argc, char **argv) {
	int i;
	int n = 0;

	for (i = 0; i < argc; ++i) {
		printf("%d\n", n);
		// printf("[%d]: %s\n",i, argv[i]);
		foo(argv[i]);
	}
}
