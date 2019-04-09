#include	"unpxti.h"

#define	NREAD	100

int		listenfd, connfd;

int
main(int argc, char **argv)
{
	int		n, flags;
	char	buff[NREAD+1];		/* +1 for null at end */
	struct pollfd	pollfd[1];

	if (argc == 2)
		listenfd = Tcp_listen(NULL, argv[1], NULL);
	else if (argc == 3)
		listenfd = Tcp_listen(argv[1], argv[2], NULL);
	else
		err_quit("usage: tcprecv04 [ <host> ] <port#>");

	connfd = Xti_accept(listenfd, NULL, NULL);
	sleep(5);

	pollfd[0].fd = connfd;
	pollfd[0].events = POLLIN;

	for ( ; ; ) {
		Poll(pollfd, 1, INFTIM);

		printf("revents = %x\n", pollfd[0].revents);
		if (pollfd[0].revents & POLLIN) {
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
}
