#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
void sig(int sig){
	printf("child die(%d)\n",getpid());
}

int main(){
	signal(SIGINT,sig);
	pause();
}
