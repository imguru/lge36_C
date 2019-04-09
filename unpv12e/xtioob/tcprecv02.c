#include	"unpxti.h"

#define	NREAD	1

int		listenfd, connfd;

void	sig_poll(int);

int
main(int argc, char **argv)
{
	int		n, flags;
	char	buff[NREAD+1];		/* +1 for null at end */

	if (argc == 2)
		listenfd = Tcp_listen(NULL, argv[1], NULL);
	else if (argc == 3)
		listenfd = Tcp_listen(argv[1], argv[2], NULL);
	else
		err_quit("usage: tcprecv02 [ <host> ] <port#>");

	connfd = Xti_accept(listenfd, NULL, NULL);

	Signal(SIGPOLL, sig_poll);
	Ioctl(connfd, I_SETSIG, S_RDNORM);

	for ( ; ; ) {
		flags = 0;
		if ( (n = t_rcv(connfd, buff, NREAD, &flags)) < 0) {
			if (t_errno == TLOOK) {
				if ( (n = T_look(connfd)) == T_ORDREL) {
					printf("received T_ORDREL\n");
					exit(0);
				} else
					err_quit("unexpected event after t_rcv: %d", n);
			}
			err_xti("t_rcv error");
		}
		buff[n] = 0;	/* null terminate */
		printf("read %d bytes: %s, flags = %s\n",
			   n, buff, Xti_flags_str(flags));
	}
}

void
sig_poll(int signo)
{
	printf("SIGPOLL received, event = %s\n", Xti_tlook_str(connfd));
}
