#include	"unpxti.h"

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

	rcvptr->udata.maxlen = MAXLINE;
	rcvptr->udata.buf = recvline;
	if (t_rcvudata(tfd, rcvptr, &flags) == 0) {
		recvline[rcvptr->udata.len] = 0;	/* null terminate */
		printf("from %s: %s", Xti_ntop_host(&rcvptr->addr), recvline);
	} else {
		if (t_errno == TLOOK) {
			T_rcvuderr(tfd, uderr);
			printf("error %ld for datagram sent to %s\n",
				   uderr->error, Xti_ntop_host(&uderr->addr));
		} else
			err_xti("t_rcvudata error");
	}
	exit(0);
}
