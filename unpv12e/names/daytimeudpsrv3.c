#include	"unp.h"
#include	<time.h>

int
main(int argc, char **argv)
{
	int				sockfd;
	ssize_t			n;
	char			buff[MAXLINE];
	time_t			ticks;
	socklen_t		addrlen, len;
	struct sockaddr	*cliaddr;

	if (argc == 2)
		sockfd = Udp_server_reuseaddr(NULL, argv[1], &addrlen);
	else if (argc == 3)
		sockfd = Udp_server_reuseaddr(argv[1], argv[2], &addrlen);
	else
		err_quit("usage: daytimeudpsrv [ <host> ] <service or port>");

	cliaddr = Malloc(addrlen);

	for ( ; ; ) {
		len = addrlen;
		n = Recvfrom(sockfd, buff, MAXLINE, 0, cliaddr, &len);
		printf("datagram from %s\n", Sock_ntop(cliaddr, len));

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        Sendto(sockfd, buff, strlen(buff), 0, cliaddr, len);
	}
}
