#include	"unpxti.h"

int
main(int argc, char **argv)
{
	int				listenfd, connfd;
	char			buff[MAXLINE];
	time_t			ticks;
	socklen_t		addrlen;
	struct netbuf	cliaddr;

	if (argc == 2)
		listenfd = Tcp_listen(NULL, argv[1], &addrlen);
	else if (argc == 3)
		listenfd = Tcp_listen(argv[1], argv[2], &addrlen);
	else
		err_quit("usage: daytimetcpsrv01 [ <host> ] <service or port>");
	cliaddr.buf = Malloc(addrlen);
	cliaddr.maxlen = addrlen;
	
	for ( ; ; ) {
		connfd = Xti_accept(listenfd, &cliaddr, 0);
		printf("connection from %s\n", Xti_ntop(&cliaddr));

		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		T_snd(connfd, buff, strlen(buff), 0);

		T_close(connfd);
	}
}
