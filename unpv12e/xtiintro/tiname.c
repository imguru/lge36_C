#include	"unpxti.h"

/*
 * See what the netbuf{} looks like for loopback addresses.
 * argv[1] must be from /etc/net/ticotsord/hosts and
 * argv[2] must be from /etc/net/ticotsord/services.
 */

int
main(int argc, char **argv)
{
	int					fd;

	if (argc != 3)
		err_quit("usage: tiname <hostname> <service-name>");

	fd = do_connect(argv[1], argv[2]);

	exit(0);
}

int
do_connect(const char *host, const char *serv)
{
	int					tfd, i;
	void				*handle;
	struct t_call		tcall;
	struct t_discon		tdiscon;
	struct netconfig	*ncp;
	struct nd_hostserv	hs;
	struct nd_addrlist	*alp;
	struct netbuf		*np;

	handle = Setnetpath();

	hs.h_host = (char *) host;
	hs.h_serv = (char *) serv;

	while ( (ncp = getnetpath(handle)) != NULL) {
		if (strcmp(ncp->nc_netid, "ticotsord") != 0)
			continue;

		if (netdir_getbyname(ncp, &hs, &alp) != 0)
			continue;

				/* try each server address */
		for (i = 0, np = alp->n_addrs; i < alp->n_cnt; i++, np++) {
			printf("device = %s\n", ncp->nc_device);
			if ( (tfd = t_open(ncp->nc_device, O_RDWR, NULL)) < 0)
				err_xti("t_open error for %s", ncp->nc_device);
		
			if (t_bind(tfd, NULL, NULL) < 0)
				err_xti("t_bind error");

			tcall.addr.len  = np->len;
			tcall.addr.buf  = np->buf;	/* pointer copy */
			printf("addr.len = %d\n", tcall.addr.len);
			printf("addr.buf = %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n",
					tcall.addr.buf[0], tcall.addr.buf[1],
					tcall.addr.buf[2], tcall.addr.buf[3],
					tcall.addr.buf[4], tcall.addr.buf[5],
					tcall.addr.buf[6], tcall.addr.buf[7],
					tcall.addr.buf[8], tcall.addr.buf[9],
					tcall.addr.buf[10]);
		}
		netdir_free(alp, ND_ADDRLIST);
	}
	endnetpath(handle);
	return(-1);
}
