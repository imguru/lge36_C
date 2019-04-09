#include	"unpxti.h"

int
main(int argc, char **argv)
{
	int				listenfd, connfd;
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
	
	sleep(20);
	for ( ; ; ) {
		T_listen(listenfd, tcallp);
		printf("connection from %s, seq %d\n",
				Xti_ntop(&tcallp->addr), tcallp->sequence);

		connfd = T_open(xti_serv_dev, O_RDWR, NULL);
		if (t_accept(listenfd, connfd, tcallp)== -1)
			err_xti("t_accept error, event = %d", t_look(listenfd));

		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		T_snd(connfd, buff, strlen(buff), 0);

		T_close(connfd);
	}
}
