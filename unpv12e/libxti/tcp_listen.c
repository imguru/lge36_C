/* include tcp_listen */
#include	"unpxti.h"
#include	<limits.h>		/* PATH_MAX */

char	xti_serv_dev[PATH_MAX + 1];

int
tcp_listen(const char *host, const char *serv, socklen_t *addrlenp)
{
	int					listenfd;
	void				*handle;
	char				*ptr;
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
		   strcmp(ncp->nc_proto, "tcp") != 0)
			;

	if (ncp == NULL)
		return(-1);

	if (netdir_getbyname(ncp, &hs, &alp) != 0) {
		endnetconfig(handle);
		return(-2);
	}
	np = alp->n_addrs;		/* use first address */

	listenfd = T_open(ncp->nc_device, O_RDWR, &tinfo);
	strncpy(xti_serv_dev, ncp->nc_device, sizeof(xti_serv_dev));

	tbind.addr = *np;		/* copy entire netbuf{} */
		/*4can override LISTENQ constant with environment variable */
	if ( (ptr = getenv("LISTENQ")) != NULL)
		tbind.qlen = atoi(ptr);
	else
		tbind.qlen = LISTENQ;
	T_bind(listenfd, &tbind, NULL);

	netdir_free(alp, ND_ADDRLIST);
	endnetconfig(handle);

	if (addrlenp)
		*addrlenp = tinfo.addr;	/* size of protocol addresses */
	return(listenfd);
}
/* end tcp_listen */

/*
 * We place the wrapper function here, not in wrapxti.c, because some
 * XTI programs need to include ../lib/wraplib.c, and it also defines
 * a Tcp_listen() function.
 */

int
Tcp_listen(const char *host, const char *serv, socklen_t *addrlenp)
{
	int		n;

	if ( (n = tcp_listen(host, serv, addrlenp)) < 0) {
		err_quit("tcp_listen error for %s, %s: %s",
				 host, serv, gai_strerror(-n));
	}
	return(n);
}
