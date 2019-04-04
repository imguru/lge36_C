#include <stdio.h>
#include <signal.h>

void sig_int(int signo) {
	printf("SIGINT\n");
}

int main() {
	char buf[32];
	// signal(SIGINT, sig_int); // SA_RESTART
	struct sigaction action = {0, };
	action.sa_handler = sig_int;
	action.sa_flags = SA_RESTART;

	sigaction(SIGINT, &action, NULL);

	read(0, buf, sizeof buf);
	printf("after read\n");
}
