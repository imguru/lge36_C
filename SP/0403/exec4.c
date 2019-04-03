#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>

int main() {
	pid_t pid;

	printf("program 시작\n");
	
	if ((pid = fork()) == 0) {
		if (execlp("ls", "ls", "-i", "-l", (char*)0) == -1) {
			perror("execlp");
		}

		exit(1);
	} 

	wait(NULL);
	printf("program 종료\n");
}









