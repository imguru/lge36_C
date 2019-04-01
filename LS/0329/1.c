
#include <stdio.h>

void foo() {
	char *str = "hello";
	str[0] = 'x';

	printf("%s\n", str);
}

int main() {
	// char str[] = "hello";
	foo();
}

