/* include udp_client */
#include	"unpxti.h"

int
udp_client(const char *host, const char *serv, void **vptr, socklen_t *lenp)
{
	int					tfd;
	void				*handle;
	struct netconfig	*ncp;
	struct nd_hostserv	hs;
	struct nd_addrlist	*alp;
	struct netbuf		*np;
	struct t_unitdata	*tudptr;

	handle = Setnetpath();

	hs.h_host = (char *) host;
	hs.h_serv = (char *) serv;

	while ( (ncp = getnetpath(handle)) != NULL) {
		if (strcmp(ncp->nc_proto, "udp") != 0)
			continue;

		if (netdir_getbyname(ncp, &hs, &alp) != 0)
			continue;

		tfd = T_open(ncp->nc_device, O_RDWR, NULL);
	
		T_bind(tfd, NULL, NULL);

		tudptr = T_alloc(tfd, T_UNITDATA, T_ADDR);

		np = alp->n_addrs;				/* use first server address */
		tudptr->addr.len = min(tudptr->addr.maxlen, np->len);
		memcpy(tudptr->addr.buf, np->buf, tudptr->addr.len);
	
		endnetpath(handle);
		netdir_free(alp, ND_ADDRLIST);

		*vptr = tudptr;				/* return pointer to t_unitdata{} */
		*lenp = tudptr->addr.maxlen;/* and size of addresses */
		return(tfd);
	}
	endnetpath(handle);
	return(-1);
}
/* end udp_client */

int
Udp_client(const char *host, const char *serv, void **vptr, socklen_t *lenp)
{
	int		n;

	if ( (n = udp_client(host, serv, vptr, lenp)) < 0)
       	err_quit("udp_client error for %s, %s", host, serv);
	return(n);
}
