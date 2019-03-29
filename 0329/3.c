#include <stdio.h>
#include <string.h>

char *gPtr;

int main(int argc, char **argv)
{
	strcpy(gPtr, "abcd");			
	printf("%s\n", gPtr);

	return 0;
}

