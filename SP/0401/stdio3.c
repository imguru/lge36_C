
#include <stdio.h>

// stdin  -> 0 -> /dev/console
// stdout -> 1 -> /dev/console
int main() {
	int age;

	printf("age: ");
	scanf("%d", &age);
}
