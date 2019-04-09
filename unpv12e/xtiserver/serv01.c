/* include serv01 */
#include	"unpxti.h"

int
main(int argc, char **argv)
{
	int				listenfd, connfd;
	pid_t			childpid;
	void			sig_chld(int), sig_int(int), web_child(int);
	socklen_t		addrlen;
	struct netbuf	cliaddr;

	if (argc == 2)
		listenfd = Tcp_listen(NULL, argv[1], &addrlen);
	else if (argc == 3)
		listenfd = Tcp_listen(argv[1], argv[2], &addrlen);
	else
		err_quit("usage: serv01 [ <host> ] <port#>");
	cliaddr.buf = Malloc(addrlen);
	cliaddr.maxlen = addrlen;

	Signal(SIGCHLD, sig_chld);
	Signal(SIGINT, sig_int);

	for ( ; ; ) {
		connfd = Xti_accept(listenfd, &cliaddr, 1);
		printf("connection from %s\n", Xti_ntop(&cliaddr));

		if ( (childpid = Fork()) == 0) {	/* child process */
			Close(listenfd);	/* close listening socket */
			web_child(connfd);	/* process the request */
			exit(0);
		}
		Close(connfd);			/* parent closes connected socket */
	}
}
/* end serv01 */

void
sig_int(int signo)
{
	void	xti_accept_dump(void);

	xti_accept_dump();
	exit(0);
}
