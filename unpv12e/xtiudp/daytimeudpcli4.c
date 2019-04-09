#include	"unpxti.h"

#undef	MAXLINE
#define	MAXLINE	2

int
main(int argc, char **argv)
{
	int					tfd, flags;
	char				recvline[MAXLINE + 1];
	socklen_t			addrlen;
	struct t_unitdata	*sndptr, *rcvptr;
	struct t_uderr		*uderr;

	if (argc != 3)
		err_quit("usage: a.out <hostname or IPaddress> <service or port#>");

	tfd = Udp_client(argv[1], argv[2], (void **) &sndptr, &addrlen);

	rcvptr = T_alloc(tfd, T_UNITDATA, T_ADDR);
	uderr = T_alloc(tfd, T_UDERROR, T_ADDR);

	printf("sending to %s\n", Xti_ntop_host(&sndptr->addr));

	sndptr->udata.maxlen = MAXLINE;
	sndptr->udata.len = 1;
	sndptr->udata.buf = recvline;
	recvline[0] = 0;		/* 1-byte datagram containing null byte */
	T_sndudata(tfd, sndptr);

	do {
		rcvptr->udata.maxlen = MAXLINE;
		rcvptr->udata.buf = recvline;
		flags = 0;
		if (t_rcvudata(tfd, rcvptr, &flags) == 0) {
			recvline[rcvptr->udata.len] = 0;	/* null terminate */
			if (rcvptr->addr.len > 0)
				printf("from %s: ", Xti_ntop_host(&rcvptr->addr));
			printf("%s\n", recvline);
		} else {
			if (t_errno == TLOOK) {
				T_rcvuderr(tfd, uderr);
				printf("error %ld from %s\n",
						uderr->error, Xti_ntop_host(&uderr->addr));
			} else
				err_xti("t_rcvudata error");
			flags = 0;
		}
	} while (flags & T_MORE);
	exit(0);
}
