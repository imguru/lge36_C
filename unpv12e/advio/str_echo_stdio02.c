#include	"unp.h"

void
str_echo(int sockfd)
{
	char		line[MAXLINE];
	FILE		*fpin, *fpout;

	fpin = Fdopen(sockfd, "r");
	fpout = Fdopen(sockfd, "w");

	for ( ; ; ) {
		if (Fgets(line, MAXLINE, fpin) == NULL)
			return;		/* connection closed by other end */

		Fputs(line, fpout);
	}
}
