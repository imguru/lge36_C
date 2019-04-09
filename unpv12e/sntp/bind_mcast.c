#include	"sntp.h"

void
bind_mcast(const char *ifname, SA *mcastsa, socklen_t salen, int alias)
{
#ifdef	MCAST
	int				fd;
	struct sockaddr	*msa;

	if (alias)
		return;		/* only one mcast join per interface */

	printf("joining %s on %s\n", Sock_ntop_host(mcastsa, salen), ifname);

	fd = Socket(mcastsa->sa_family, SOCK_DGRAM, 0);

	Setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	Bind(fd, mcastsa, salen);

	Mcast_join(fd, mcastsa, salen, ifname, 0);

	addrs[naddrs].addr_sa = mcastsa;
	addrs[naddrs].addr_salen = salen;
	addrs[naddrs].addr_ifname = ifname;	/* save pointer, not string copy */
	addrs[naddrs].addr_fd = fd;
	addrs[naddrs].addr_flags = ADDR_MCAST;
	naddrs++;
#endif
}
