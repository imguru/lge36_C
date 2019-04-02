#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include <stdio.h>
#include <stdlib.h> // qsort
#include <string.h>

int name_compare(const void *a, const void *b) {
	char *s1 = *(char **)a;
	char *s2 = *(char **)b;

	return strcmp(s1, s2);
}

int main(int argc, char **argv) {
	DIR *dp;
	struct dirent *dir;
	struct stat buf;
	int i, j;

	char *files[1024];
	int n = 0;

	dp = opendir(".");
	while ((dir = readdir(dp)) != NULL) {
		files[n++] = dir->d_name;
	}

	qsort(files, n, sizeof(files[0]), &name_compare);
	for (i = 0; i < n; ++i) {
		char perms[11] = "----------";

		if (files[i][0] == '.') {
			continue;
		}

		lstat(files[i], &buf);

		if (S_ISREG(buf.st_mode)) {
			perms[0] = '-';
		} else if (S_ISDIR(buf.st_mode)) {
			perms[0] = 'd';
		} else if (S_ISLNK(buf.st_mode)) {
			perms[0] = 'l';
		} else if (S_ISFIFO(buf.st_mode)) {
			perms[0] = 'p';
		} else if (S_ISSOCK(buf.st_mode)) {
			perms[0] = 's';
		} else if (S_ISCHR(buf.st_mode)) {
			perms[0] = 'c';
		} else if (S_ISBLK(buf.st_mode)) {
			perms[0] = 'b';
		}

		for (j = 0; j < 9; ++j) {
			if (buf.st_mode >> (8 - j) & 0x1) {
				perms[1+j] = "rwx"[j%3];
			}
		}

		printf("%s %s\n", perms, files[i]);
	}

	closedir(dp);
	return 0;
}






