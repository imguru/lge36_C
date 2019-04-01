#include <stdio.h>

int main()
{
	char buff[100];
	int ret;

	FILE *fp;
	fp = fopen("hello.txt", "r");
	ret = fread( buff, 1, 2, fp);
	fwrite( buff, 1, ret , stdout ); 
	getchar();

	ret = fread( buff, 1, 2, fp);
	fwrite( buff, 1, ret , stdout ); 
	fclose(fp);
	return 0;
}

