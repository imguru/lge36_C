#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

#include <stdio.h>
#include <stdlib.h>

//  : getopt
//    int getopt(int argc, char * const argv[], const char *optstring);
int main(int argc, char **argv) {
	DIR *dp;
	struct dirent *dir;
	int opt;

	while ((opt = getopt(argc, argv, "alRi")) != -1) {
		switch (opt) {
			case 'a':
				printf("-a\n");
				break;
			case 'l':
				printf("-l\n");
				break;
			case 'R':
				printf("-R\n");
				break;
			case 'i':
				printf("-i\n");
				break;
			default:
				fprintf(stderr, "Invalid option - %c\n", opt);
				exit(1);
		}

	}

	dp = opendir(".");
	if (dp == NULL) {
		fprintf(stderr, "directory open error..\n");
		return 1;
	}

	while ((dir = readdir(dp)) != NULL) {
		printf("%lu - %s\n", dir->d_ino, dir->d_name);
	}

	closedir(dp);
	return 0;
}





























