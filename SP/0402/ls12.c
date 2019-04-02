#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void my_ls(char *dname) {
	DIR *dp;
	struct dirent *dir;
	struct stat buf;

	printf("\n%s: \n", dname);
	dp = opendir(dname);
	if (dp == NULL) {
		fprintf(stderr, "directory open error - %s\n", dname);
		exit(1);
	}

	// 현재 작업 디렉토리를 변경한다.
	chdir(dname);

	// 현재 디렉토리의 내용을 먼저 출력한다.
	while ((dir = readdir(dp)) != NULL) {
		if (dir->d_name[0] != '.')
			printf("%s\n", dir->d_name);
	}

	// DIR*는 스트림이다.
	// 끝까지 읽었으면, 다시 처음으로 되돌려야 한다.!!
	rewinddir(dp);

	// 현재 디렉토리의 파일 중 디렉토리가 있다면 재귀 순회한다.
	while ((dir = readdir(dp)) != NULL) {
		if (lstat(dir->d_name, &buf) == -1) {
			fprintf(stderr, "lstat error - %s\n", dir->d_name);
			exit(1);
		}

		if (S_ISDIR(buf.st_mode)) {
			if (strcmp(dir->d_name, ".") == 0 || 
					strcmp(dir->d_name, "..") == 0) {
				continue;
			}
			
			my_ls(dir->d_name); 
		}
	}

	closedir(dp);
	
	// 다시 복구한다.
	chdir("..");
	printf("\n");
}

int main() {
	my_ls(".");
	return 0;
}


































