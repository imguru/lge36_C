#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/stat.h>

int main(void) {
	FILE *fp;
	char readbuf[80];

	umask(0);
	//                        rw-rw-rw-
	mknod("myfifo", S_IFIFO | 0666, 0);

	while(1)
	{
		fp = fopen("myfifo", "r");
		fgets(readbuf, 80, fp);
		printf("Received string: %s\n", readbuf);
		fclose(fp);
	}
	return(0);
}

