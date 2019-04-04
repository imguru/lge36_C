#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static void sig_quit(int signo){
	printf("caught SIGQUIT\n");

	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		printf("can't reset SIGQUIT");
	return;
}

static void sig_int(int signo) {
	printf("caught SIGINT\n");
}

int main(void){
	sigset_t newmask, oldmask, pendmask;

	if (signal(SIGQUIT, sig_quit) == SIG_ERR)
		printf("can't catch SIGQUIT");
	if (signal(SIGINT, sig_int) == SIG_ERR)
		printf("can't catch SIGINT");

	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);
	sigaddset(&newmask, SIGINT);

	/* block SIGQUIT and save current signal mask */
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		printf("SIG_BLOCK error");

	sleep(10);       /* SIGQUIT here will remain pending */
	printf("end sleep(10)\n");

#if 1
	if (sigpending(&pendmask) < 0)
		printf("sigpending error");
	if (sigismember(&pendmask, SIGQUIT))
		printf("\nSIGQUIT pending\n");
	if (sigismember(&pendmask, SIGINT))
		printf("\nSIGINT pending\n");
#endif

	printf("before sigprocmask..\n");
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		printf("SIG_SETMASK error");
	printf("SIGQUIT unblocked\n");
	sleep(5);       /* SIGQUIT here will terminate with core file */
	exit(0);
}

