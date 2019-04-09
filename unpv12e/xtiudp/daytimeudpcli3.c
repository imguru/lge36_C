#include	"unpxti.h"

int
main(int argc, char **argv)
{
	int					tfd, flags;
	char				recvline[MAXLINE + 1];
	socklen_t			addrlen;
	struct t_unitdata	*sndptr1, *sndptr2, *sndptr3, *rcvptr;
	struct t_uderr		*uderr;

	if (argc != 5)
		err_quit("usage: a.out <host1> <host2> <host3> <service or port#>");

	tfd = Udp_client(argv[1], argv[4], (void **) &sndptr1, &addrlen);
	close(tfd);
	tfd = Udp_client(argv[2], argv[4], (void **) &sndptr2, &addrlen);
	close(tfd);
	tfd = Udp_client(argv[3], argv[4], (void **) &sndptr3, &addrlen);

	rcvptr = T_alloc(tfd, T_UNITDATA, T_ADDR);
	uderr = T_alloc(tfd, T_UDERROR, T_ADDR);

	printf("sending to %s\n", Xti_ntop_host(&sndptr1->addr));
	sndptr1->udata.maxlen = MAXLINE;
	sndptr1->udata.len = 1;
	sndptr1->udata.buf = recvline;
	recvline[0] = 0;		/* 1-byte datagram containing null byte */
	T_sndudata(tfd, sndptr1);

	printf("sending to %s\n", Xti_ntop_host(&sndptr2->addr));
	sndptr2->udata.maxlen = MAXLINE;
	sndptr2->udata.len = 1;
	sndptr2->udata.buf = recvline;
	*(sndptr2->udata.buf) = 0;
	T_sndudata(tfd, sndptr2);

	printf("sending to %s\n", Xti_ntop_host(&sndptr3->addr));
	sndptr3->udata.maxlen = MAXLINE;
	sndptr3->udata.len = 1;
	sndptr3->udata.buf = recvline;
	*(sndptr3->udata.buf) = 0;
	T_sndudata(tfd, sndptr3);

	for ( ; ; ) {
		rcvptr->udata.maxlen = MAXLINE;
		rcvptr->udata.buf = recvline;
		if (t_rcvudata(tfd, rcvptr, &flags) == 0) {
			recvline[rcvptr->udata.len] = 0;	/* null terminate */
			printf("from %s: %s", Xti_ntop_host(&rcvptr->addr), recvline);
		} else {
			if (t_errno == TLOOK) {
				T_rcvuderr(tfd, uderr);
				printf("error %ld from %s\n",
					   uderr->error, Xti_ntop_host(&uderr->addr));
			} else
				err_xti("t_rcvudata error");
		}
	}
	exit(0);
}
