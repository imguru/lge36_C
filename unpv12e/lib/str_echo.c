#include	"unp.h"

void
str_echo(int sockfd)
{
	ssize_t		n;
	char		line[MAXLINE];

	for ( ; ; ) {
		if ( (n = Readline(sockfd, line, MAXLINE)) == 0)
			return;		/* connection closed by other end */

		Writen(sockfd, line, n);
	}
}
