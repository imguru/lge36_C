#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include <stdio.h>
#include <stdlib.h>

// stat
// int stat(const char *pathname, struct stat *buf);
// int lstat(const char *pathname, struct stat *buf);
//  : 심볼링 링크 파일의 정보를 확인하고 싶다면,
//    lstat 함수를 이용해야 합니다.

int main(int argc, char **argv) {
	DIR *dp;
	struct dirent *dir;
	int opt;
	struct stat buf;

	dp = opendir(".");
	if (dp == NULL) {
		fprintf(stderr, "directory open error..\n");
		return 1;
	}

	while ((dir = readdir(dp)) != NULL) {
		if (dir->d_name[0] == '.') {
			continue;
		}

		lstat(dir->d_name, &buf);

		if (S_ISREG(buf.st_mode)) {
			printf("- ");
		} else if (S_ISDIR(buf.st_mode)) {
			printf("d ");
		} else if (S_ISLNK(buf.st_mode)) {
			printf("l ");
		} else if (S_ISFIFO(buf.st_mode)) {
			printf("p ");
		} else if (S_ISSOCK(buf.st_mode)) {
			printf("s ");
		} else if (S_ISCHR(buf.st_mode)) {
			printf("c ");
		} else if (S_ISBLK(buf.st_mode)) {
			printf("b ");
		}

		printf(" %s\n", dir->d_name);
	}

	closedir(dp);
	return 0;
}






