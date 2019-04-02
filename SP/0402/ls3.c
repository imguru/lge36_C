#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

#include <stdio.h>
#include <stdlib.h>

#define OPTION_ALL       (1<<0) // 00000001
#define OPTION_LIST      (1<<1) // 00000010
#define OPTION_RECURSIVE (1<<2) // 00000100
#define OPTION_INODE     (1<<3) // 00001000

int main(int argc, char **argv) {
	DIR *dp;
	struct dirent *dir;
	int opt;

	int options = 0;

	while ((opt = getopt(argc, argv, "alRi")) != -1) {
		switch (opt) {
			case 'a':
				options |= OPTION_ALL;
				break;
			case 'l':
				options |= OPTION_LIST;
				break;
			case 'R':
				options |= OPTION_RECURSIVE;
				break;
			case 'i':
				options |= OPTION_INODE;
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
		if ( !(options & OPTION_ALL) && dir->d_name[0] == '.') {
			continue;
		}

		printf("%lu - %s\n", dir->d_ino, dir->d_name);
	}

	closedir(dp);
	return 0;
}

#if 0
int main(int argc, char **argv) {
	DIR *dp;
	struct dirent *dir;
	int opt;

	int option_a = 0;
	int option_l = 0;
	int option_R = 0;
	int option_i = 0;

	while ((opt = getopt(argc, argv, "alRi")) != -1) {
		switch (opt) {
			case 'a':
				option_a = 1;
				break;
			case 'l':
				option_l = 1;
				break;
			case 'R':
				option_R = 1;
				break;
			case 'i':
				option_i = 1;
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
		if (!option_a && dir->d_name[0] == '.') {
			continue;
		}

		printf("%lu - %s\n", dir->d_ino, dir->d_name);
	}

	closedir(dp);
	return 0;
}
#endif





























