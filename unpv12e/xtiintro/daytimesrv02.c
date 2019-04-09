#include	"unpxti.h"

int
main(int argc, char **argv)
{
	int				listenfd, connfd, n, flags = 0;
	char			buff[MAXLINE];
	time_t			ticks;
	struct t_call	*tcallp;

	if (argc == 2)
		listenfd = Tcp_listen(NULL, argv[1], NULL);
	else if (argc == 3)
		listenfd = Tcp_listen(argv[1], argv[2], NULL);
	else
		err_quit("usage: daytimetcpsrv [ <host> ] <service or port>");

	tcallp = T_alloc(listenfd, T_CALL, T_ALL);
	
	for ( ; ; ) {
		if (t_listen(listenfd, tcallp) == -1)
			err_xti("t_listen error");
		printf("connection from %s, seq %d\n",
				Xti_ntop(&tcallp->addr), tcallp->sequence);

		connfd = T_open(xti_serv_dev, O_RDWR, NULL);
		T_bind(connfd, NULL, NULL);
		T_accept(listenfd, connfd, tcallp);

		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		T_snd(connfd, buff, strlen(buff), 0);

		T_sndrel(connfd);
		while ( (n = t_rcv(connfd, buff, MAXLINE, &flags)) >= 0)
			;
		if (t_errno == TLOOK) {
			if ( (n = T_look(connfd)) == T_ORDREL) {
				T_rcvrel(connfd);
				printf("t_rcvrel returned at %s\n", gf_time());
			} else if (n == T_DISCONNECT) {
				T_rcvdis(connfd, NULL);
				printf("t_rcvdis returned at %s\n", gf_time());
			}
		} else
			err_xti("t_rcv error");
		T_close(connfd);
	}
}
