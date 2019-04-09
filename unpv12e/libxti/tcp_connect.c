/* include tcp_connect */
#include	"unpxti.h"

int
tcp_connect(const char *host, const char *serv)
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
		if (strcmp(ncp->nc_proto, "tcp") != 0)
			continue;

		if (netdir_getbyname(ncp, &hs, &alp) != 0)
			continue;

			/*4try each server address */
		for (i = 0, np = alp->n_addrs; i < alp->n_cnt; i++, np++) {
			tfd = T_open(ncp->nc_device, O_RDWR, NULL);
		
			T_bind(tfd, NULL, NULL);

			tcall.addr.len  = np->len;
			tcall.addr.buf  = np->buf;	/* pointer copy */
			tcall.opt.len   = 0;		/* no options */
			tcall.udata.len = 0;		/* no user data with connect */
		
			if (t_connect(tfd, &tcall, NULL) == 0) {
				endnetpath(handle);		/* success, connected to server */
				netdir_free(alp, ND_ADDRLIST);
				return(tfd);
			}

			if (t_errno == TLOOK && t_look(tfd) == T_DISCONNECT) {
				t_rcvdis(tfd, &tdiscon);
				errno = tdiscon.reason;
			}
			t_close(tfd);
		}
		netdir_free(alp, ND_ADDRLIST);
	}
	endnetpath(handle);
	return(-1);
}
/* end tcp_connect */

/*
 * We place the wrapper function here, not in wrapxti.c, because some
 * XTI programs need to include ../lib/wraplib.c, and it also defines
 * a Tcp_connect() function.
 */

int
Tcp_connect(const char *host, const char *serv)
{
	int		n;

	if ( (n = tcp_connect(host, serv)) < 0)
       	err_sys("tcp_connect error for %s, %s", host, serv);
			/* assumes tcp_connect() has set errno */
	return(n);
}
