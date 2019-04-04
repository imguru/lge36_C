
#include <unistd.h>
#include <stdio.h>

#include <signal.h>

void foo(int signum) {
	printf("알람...\n");
	alarm(1);
}

int main() {
	signal(SIGALRM, &foo);
	printf("%d\n", getpid());

	alarm(3);

	while (1)
		pause();
}
