/* include mcast_join1 */
#include	"unp.h"
#include	<net/if.h>

int
mcast_join(int sockfd, const SA *sa, socklen_t salen,
		   const char *ifname, u_int ifindex)
{
	switch (sa->sa_family) {
	case AF_INET: {
		struct ip_mreq		mreq;
		struct ifreq		ifreq;

		memcpy(&mreq.imr_multiaddr,
			   &((struct sockaddr_in *) sa)->sin_addr,
			   sizeof(struct in_addr));

		if (ifindex > 0) {
			if (if_indextoname(ifindex, ifreq.ifr_name) == NULL) {
				errno = ENXIO;	/* i/f index not found */
				return(-1);
			}
			goto doioctl;
		} else if (ifname != NULL) {
			strncpy(ifreq.ifr_name, ifname, IFNAMSIZ);
doioctl:
			if (ioctl(sockfd, SIOCGIFADDR, &ifreq) < 0)
				return(-1);
			memcpy(&mreq.imr_interface,
				   &((struct sockaddr_in *) &ifreq.ifr_addr)->sin_addr,
				   sizeof(struct in_addr));
		} else
			mreq.imr_interface.s_addr = htonl(INADDR_ANY);

		return(setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP,
						  &mreq, sizeof(mreq)));
	}
/* end mcast_join1 */

/* include mcast_join2 */
#ifdef	IPV6
	case AF_INET6: {
		struct ipv6_mreq	mreq6;

		memcpy(&mreq6.ipv6mr_multiaddr,
			   &((struct sockaddr_in6 *) sa)->sin6_addr,
			   sizeof(struct in6_addr));

		if (ifindex > 0)
			mreq6.ipv6mr_interface = ifindex;
		else if (ifname != NULL)
			if ( (mreq6.ipv6mr_interface = if_nametoindex(ifname)) == 0) {
				errno = ENXIO;	/* i/f name not found */
				return(-1);
			}
		else
			mreq6.ipv6mr_interface = 0;

		return(setsockopt(sockfd, IPPROTO_IPV6, IPV6_ADD_MEMBERSHIP,
						  &mreq6, sizeof(mreq6)));
	}
#endif

	default:
		errno = EPROTONOSUPPORT;
		return(-1);
	}
}
/* end mcast_join2 */

void
Mcast_join(int sockfd, const SA *sa, socklen_t salen,
		   const char *ifname, u_int ifindex)
{
	if (mcast_join(sockfd, sa, salen, ifname, ifindex) < 0)
		err_sys("mcast_join error");
}
