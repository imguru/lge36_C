#include	"unp.h"

void
loop(int sockfd, socklen_t salen)
{
	char			buf[MAXLINE+1];
	socklen_t		len;
	ssize_t			n;
	struct sockaddr	*sa;
	struct sap_packet {
	  uint32_t	sap_header;
	  uint32_t	sap_src;
	  char		sap_data[1];
	} *sapptr;

	sa = Malloc(salen);

	for ( ; ; ) {
		len = salen;
		n = Recvfrom(sockfd, buf, MAXLINE, 0, sa, &len);
		buf[n] = 0;			/* null terminate */

		sapptr = (struct sap_packet *) buf;
		if ( (n -= 2 * sizeof(uint32_t)) <= 0)
			err_quit("n = %d", n);
		printf("From %s\n%s\n", Sock_ntop(sa, len), sapptr->sap_data);
	}
}
