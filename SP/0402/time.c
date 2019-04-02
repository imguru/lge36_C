
#include <time.h>
#include <stdio.h>

int main() {
	time_t now = time(0);
	printf("%s", ctime(&now));
}
