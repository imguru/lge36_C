
#include <stdio.h>

int main() {
	int n;
	char c;

	scanf("%d", &n);
	// fflush(stdin); // 표준이 아닙니다. 

	// getchar();

	scanf(" %c", &c);

	printf("n=%d c=%c\n", n, c);
}
