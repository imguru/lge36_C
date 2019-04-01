#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
	int fd;           // FILE *fp;
	int ret;
	char buf[100];

	// fp = fopen("a.c", "r");
	fd = open("syscall.c", O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "file open error...\n");
		return 1;
	}

#if 0
	while( ret = fread( buff, 1, sizeof buff, fp ) )
		fwrite( buff, 1, ret , stdout );
#endif
	// read
	//   ret==0 : EOF
	//   ret==-1: Error
	//   ret>0  : 읽은 바이트 수
	while ((ret = read(fd, buf, sizeof buf)) > 0) {
		write(1, buf, ret);
	}

	// fclose(fp);
	close(fd);

}

#if 0
int main()
{
	FILE *fp;
	int ret;
	char buff[100];

	fp = fopen("a.c", "r");
	while( ret = fread( buff, 1, sizeof buff, fp ) )
		fwrite( buff, 1, ret , stdout );
	fclose(fp);


	return 0;
}
#endif
