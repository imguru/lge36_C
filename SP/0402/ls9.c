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

int get_width(long value) {
	int n = 0;
	while (value > 0) {
		value /= 10;
		++n;
	}

	return n;
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
	int n = 0;

	dp = opendir(".");
	while ((dir = readdir(dp)) != NULL) {
		files[n++] = dir->d_name;
		lstat(dir->d_name, &buf);

		temp_width = get_width(buf.st_size);
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

#if 0
		struct tm {
			int tm_sec;    /* Seconds (0-60) */
			int tm_min;    /* Minutes (0-59) */
			int tm_hour;   /* Hours (0-23) */
			int tm_mday;   /* Day of the month (1-31) */
			int tm_mon;    /* Month (0-11) */
			int tm_year;   /* Year - 1900 */
			int tm_wday;   /* Day of the week (0-6, Sunday = 0) */
			int tm_yday;   /* Day in the year (0-365, 1 Jan = 0) */
			int tm_isdst;  /* Daylight saving time */
		};
#endif

		// buf.st_mtime // time_t(epoch time) -> 4월  2 11:28

		// buf.st_uid: 파일 소유자의 User ID(getpwuid -> 문자열)
		// buf.st_gid: 파일 소유자의 Group ID(getgrgid
		tm = localtime(&buf.st_mtime);
		// 4월  2 11:28
		sprintf(timestr, "%d월 %2d %02d:%02d",
				tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min);

		printf("%s %lu %s %s %*ld %s %s\n", 
				perms, buf.st_nlink, 
				getpwuid(buf.st_uid)->pw_name, 
				getgrgid(buf.st_gid)->gr_name,
				width, buf.st_size,
				timestr,
				files[i]);
	}

	closedir(dp);
	return 0;
}













