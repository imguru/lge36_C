#include <unistd.h>
#include <stdio.h>
#include <signal.h>

#define NUMCHILD 3

int main(int argc, char *argv[]){
	int pid, chpid[NUMCHILD];
	int i, status;

	for(i=0;i<NUMCHILD;i++)  {
		if((pid=fork())==0)
			execlp("./sig_child","./sig_child",
					(char *)0);
		chpid[i] = pid;
	}

	printf("sig_parent : %d child process run\n",NUMCHILD);
	sleep(10);

	kill(0, SIGINT);
#if 0
	for(i=0;i<NUMCHILD;i++)
		kill(chpid[i],SIGINT);
#endif
}

