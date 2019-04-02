#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>    // getpwuid
#include <grp.h>    // getgrgid
#include <time.h>

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
	struct tm *tm;
	int i, j;
	int width = 1;
	int temp_width = 0;

	char *files[1024];
	char timestr[128];
	char sizestr[32];
	int n = 0;

	dp = opendir(".");
	while ((dir = readdir(dp)) != NULL) {
		files[n++] = dir->d_name;
		lstat(dir->d_name, &buf);

		if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode)) {
			sprintf(sizestr, "%lu, %lu", 
					(buf.st_rdev >> 8) & 0xff, buf.st_rdev & 0xff);
		} else {
			sprintf(sizestr, "%ld", buf.st_size);
		}

		temp_width = strlen(sizestr);
		if (temp_width > width) {
			width = temp_width;
		}
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

		// Set User ID Bit
		if (S_ISUID & buf.st_mode) {
			perms[3] = perms[3] == 'x' ? 's' : 'S';
		} 
		// Set Group ID Bit
		if (S_ISGID & buf.st_mode) {
			perms[6] = perms[6] == 'x' ? 's' : 'S';
		}
		// Sticky Bit
		if (S_ISVTX & buf.st_mode) {
			perms[9] = perms[9] == 'x' ? 't' : 'T';
		}

		tm = localtime(&buf.st_mtime);
		sprintf(timestr, "%d월 %2d %02d:%02d",
				tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min);

		if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode)) {
			sprintf(sizestr, "%u, %u", 
					major(buf.st_rdev), minor(buf.st_rdev));
		} else {
			sprintf(sizestr, "%ld", buf.st_size);
		}

		printf("%s %lu %s %s %*s %s %s\n", 
				perms, buf.st_nlink, 
				getpwuid(buf.st_uid)->pw_name, 
				getgrgid(buf.st_gid)->gr_name,
				width, sizestr,  // !!!!!!!!!!
				timestr,
				files[i]);
	}

	closedir(dp);
	return 0;
}













