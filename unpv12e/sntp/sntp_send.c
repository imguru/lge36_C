#include	"sntp.h"

void
sntp_send(void)
{
	int				fd;
	Addrs			*aptr;
	struct ntpdata	msg;

		/* 4use the socket bound to 0.0.0.0/123 for sending */
	fd = addrs[naddrs-1].addr_fd;
	Setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));

	bzero(&msg, sizeof(msg));
	msg.status = (0 << 6) | (3 << 3) | MODE_CLIENT;	/* see RFC 2030 */

	for (aptr = &addrs[0]; aptr < &addrs[naddrs]; aptr++) {
		if (aptr->addr_flags & ADDR_BCAST) {
			printf("sending broadcast to %s\n",
				   Sock_ntop(aptr->addr_sa, aptr->addr_salen));
			Sendto(fd, &msg, sizeof(msg), 0,
				   aptr->addr_sa, aptr->addr_salen);
		}
#ifdef	MCAST
		if (aptr->addr_flags & ADDR_MCAST) {
				/* 4must first set outgoing i/f appropriately */
			Mcast_set_if(fd, aptr->addr_ifname, 0);
			Mcast_set_loop(fd, 0);		/* disable loopback */

			printf("sending multicast to %s on %s\n",
				   Sock_ntop(aptr->addr_sa, aptr->addr_salen),
				   aptr->addr_ifname);
			Sendto(fd, &msg, sizeof(msg), 0,
				   aptr->addr_sa, aptr->addr_salen);
		}
#endif
	}
}
