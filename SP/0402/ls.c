#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

#include <stdio.h>

// 1. 디렉토리 파일의 데이터에 해당 디렉토리에 
//    존재하는 파일의 이름이 존재한다.
// 2. 리눅스는 디렉토리의 내용을 쉽게 읽을 수 있는 함수를 제공합니다.
//    opendir
//    readdir
//    closedir

// 1. DIR *opendir(const char *name);
// stream: offset

// 2. struct dirent *readdir(DIR *dirp);
int main() {
	DIR *dp;
	struct dirent *dir;

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





























