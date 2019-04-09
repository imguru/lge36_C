#include	"unpxti.h"

int
main(int argc, char **argv)
{
	int				tfd, n, flags;
	char			recvline[MAXLINE + 1];
	struct t_bind	*bound, *peer;
	struct t_discon	tdiscon;

	if (argc != 3)
		err_quit("usage: daytimecli02 <hostname/IPaddress> <service/port#>");

	tfd = Tcp_connect(argv[1], argv[2]);

	bound = T_alloc(tfd, T_BIND, T_ALL);
	peer = T_alloc(tfd, T_BIND, T_ALL);
	T_getprotaddr(tfd, bound, peer);
	printf("connected to %s\n", Xti_ntop(&peer->addr));

	for ( ; ; ) {
		if ( (n = t_rcv(tfd, recvline, MAXLINE, &flags)) < 0) {
			if (t_errno == TLOOK) {
				if ( (n = T_look(tfd)) == T_ORDREL) {
					T_rcvrel(tfd);
					break;
				} else if (n == T_DISCONNECT) {
					T_rcvdis(tfd, &tdiscon);
					errno = tdiscon.reason; /* probably ECONNRESET */
					err_sys("server terminated prematurely");
				} else
					err_quit("unexpected event after t_rcv: %d", n);
			} else
				err_xti("t_rcv error");
		}
		recvline[n] = 0;	/* null terminate */
		fputs(recvline, stdout);
	}
	exit(0);
}
