#include	"unpxti.h"

int
main(int argc, char **argv)
{
	int					fd;
	struct t_opthdr		*topt;
	struct t_optmgmt	*req, *ret;

	if (argc != 3)
		err_quit("usage: setbufs <device> <bufsiz>");

	fd = T_open(argv[1], O_RDWR, NULL);
	printf("Device = %s\n", argv[1]);
	T_bind(fd, NULL, NULL);

	req = T_alloc(fd, T_OPTMGMT, T_ALL);
	ret = T_alloc(fd, T_OPTMGMT, T_ALL);

	topt = (struct t_opthdr *) req->opt.buf;
	topt->level = XTI_GENERIC;
	topt->name = XTI_RCVBUF;
	topt->len = sizeof(struct t_opthdr) + sizeof(u_long);
	topt->status = 0;	/* ??? */
	req->opt.len = topt->len;
	*((u_long *) (topt + 1)) = atol(argv[2]);

#ifdef	notdef
	topt = OPT_NEXTHDR(req->opt.buf, req->opt.maxlen, topt);
	topt->level = XTI_GENERIC;
	topt->name = XTI_SNDBUF;
	topt->len = sizeof(struct t_opthdr) + sizeof(u_long);
	*((u_long *) (topt + 1)) = atol(argv[2]);
	req->opt.len += topt->len;
#endif

	req->flags = T_NEGOTIATE;
	T_optmgmt(fd, req, ret);
	printf("returned flags = %ld, len = %d\n", ret->flags, ret->opt.len);

	for (topt = (struct t_opthdr *) ret->opt.buf; topt != NULL;
		 topt = OPT_NEXTHDR(ret->opt.buf, ret->opt.len, topt)) {

		if (topt->level == XTI_GENERIC && topt->name == XTI_RCVBUF) {
			printf("RCVBUF = %ld, status = %ld\n",
				   *((u_long *) (topt + 1)), topt->status);

		} else if (topt->level == XTI_GENERIC && topt->name == XTI_SNDBUF) {
			printf("SNDBUF = %ld, status = %ld\n",
				   *((u_long *) (topt + 1)), topt->status);

		} else {
			printf("unexpected option: len = %ld, level = %ld, name = %ld\n",
				   topt->len, topt->level, topt->name);
		}
	}
	exit(0);
}
