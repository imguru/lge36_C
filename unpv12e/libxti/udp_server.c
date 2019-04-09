/* include udp_server */
#include	"unpxti.h"

int
udp_server(const char *host, const char *serv, socklen_t *addrlenp)
{
	int					tfd;
	void				*handle;
	struct t_bind		tbind;
	struct t_info		tinfo;
	struct netconfig	*ncp;
	struct nd_hostserv	hs;
	struct nd_addrlist	*alp;
	struct netbuf		*np;

	handle = Setnetconfig();

	hs.h_host = (host == NULL) ? HOST_SELF : (char *) host;
	hs.h_serv = (char *) serv;

	while ( (ncp = getnetconfig(handle)) != NULL &&
		   strcmp(ncp->nc_proto, "udp") != 0)
			;

	if (ncp == NULL)
		return(-1);

	if (netdir_getbyname(ncp, &hs, &alp) != 0)
		return(-2);
	np = alp->n_addrs;		/* use first address */

	tfd = T_open(ncp->nc_device, O_RDWR, &tinfo);

	tbind.addr = *np;		/* copy entire netbuf{} */
	tbind.qlen = 0;			/* not used for connectionless server */
	T_bind(tfd, &tbind, NULL);

	endnetconfig(handle);
	netdir_free(alp, ND_ADDRLIST);

	if (addrlenp)
		*addrlenp = tinfo.addr;	/* size of protocol addresses */
	return(tfd);
}
/* end udp_server */

/*
 * We place the wrapper function here, not in wrapxti.c, because some
 * XTI programs need to include ../lib/wraplib.c, and it also defines
 * a Udp_server() function.
 */

int
Udp_server(const char *host, const char *serv, socklen_t *addrlenp)
{
	int		n;

	if ( (n = udp_server(host, serv, addrlenp)) < 0)
		err_quit("udp_server error for %s, %s", host, serv);
	return(n);
}
