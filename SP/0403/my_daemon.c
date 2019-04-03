#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#include <stdlib.h>

int daemon_init(void) {
	pid_t   pid;
	int i;
	if(fork() > 0)
		exit(0); 
	setsid();               /* become session leader */
	chdir("/");             /* change working directory */
	umask(0);               /* clear our file mode creation mask */

	for(i=0;i<64;i++)
		close(i);
	signal(SIGCLD,SIG_IGN);
	return(0);
}

int main(void)
{
	daemon_init();
	sleep(10000);
}










