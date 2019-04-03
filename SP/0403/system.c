
#include <stdio.h>
#include <stdlib.h>

int main() {
	system("ls");  // fork() -> exec(ls) -> wait();

	printf("ls end..\n");
}
