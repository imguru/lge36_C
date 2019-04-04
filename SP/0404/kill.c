#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int pid = atoi(argv[1]);

	if (kill(pid, 0) == -1) {
		perror("kill");
	}
}
