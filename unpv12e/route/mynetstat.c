#include	"unproute.h"

void	pr_rtable(void);
void	pr_iflist(void);

int
main(int argc, char **argv)
{
	pr_rtable();

	pr_iflist();

	exit(0);
}

void
pr_rtable(void)
{
	char				*buf, *next, *lim;
	size_t				len;
	struct rt_msghdr	*rtm;
	struct sockaddr		*sa, *rti_info[RTAX_MAX];

	buf = Net_rt_dump(AF_INET, 0, &len);

	lim = buf + len;
	for (next = buf; next < lim; next += rtm->rtm_msglen) {
		rtm = (struct rt_msghdr *) next;
		sa = (struct sockaddr *)(rtm + 1);
		get_rtaddrs(rtm->rtm_addrs, sa, rti_info);
		if ( (sa = rti_info[RTAX_DST]) != NULL)
			printf("dest: %s", sock_ntop(sa, sa->sa_len));

		if ( (sa = rti_info[RTAX_GATEWAY]) != NULL)
			printf(", gateway: %s", sock_ntop(sa, sa->sa_len));

		printf("\n");
	}
}

void
pr_iflist(void)
{
	int 				flags;
	char				*buf, *next, *lim;
	u_char				*ptr;
	size_t				len;
	struct if_msghdr	*ifm;
	struct ifa_msghdr	*ifam;
	struct sockaddr		*sa, *rti_info[RTAX_MAX];
	struct sockaddr_dl	*sdl;

	buf = Net_rt_iflist(0, 0, &len);

	lim = buf + len;
	for (next = buf; next < lim; next += ifm->ifm_msglen) {
		ifm = (struct if_msghdr *) next;
		if (ifm->ifm_type == RTM_IFINFO) {
			sa = (struct sockaddr *)(ifm + 1);
			get_rtaddrs(ifm->ifm_addrs, sa, rti_info);
			if ( (sa = rti_info[RTAX_IFP]) != NULL) {
				if (((flags = ifm->ifm_flags) & IFF_UP) == 0)
					continue;
				printf("interface: %s: <", Sock_ntop(sa, sa->sa_len));
				if (flags & IFF_UP)				printf("UP ");
				if (flags & IFF_BROADCAST)		printf("BCAST ");
				if (flags & IFF_MULTICAST)		printf("MCAST ");
				if (flags & IFF_LOOPBACK)		printf("LOOP ");
				if (flags & IFF_POINTOPOINT)	printf("P2P ");
				printf(">\n");

				if (sa->sa_family == AF_LINK &&
					(sdl = (struct sockaddr_dl *) sa) &&
					(sdl->sdl_alen > 0)) {
					ptr = (u_char *) &sdl->sdl_data[sdl->sdl_nlen];
					printf("  %x:%x:%x:%x:%x:%x\n", *ptr, *(ptr+1),
							*(ptr+2), *(ptr+3), *(ptr+4), *(ptr+5));
				}
			}

		} else if (ifm->ifm_type == RTM_NEWADDR) {
			ifam = (struct ifa_msghdr *) next;
			sa = (struct sockaddr *)(ifam + 1);
			get_rtaddrs(ifam->ifam_addrs, sa, rti_info);
			if ( (sa = rti_info[RTAX_IFA]) != NULL)
				printf("  IP addr: %s\n", Sock_ntop(sa, sa->sa_len));
			if ((flags & IFF_BROADCAST) && (sa = rti_info[RTAX_BRD]))
				printf("  bcast addr: %s\n", Sock_ntop(sa, sa->sa_len));

		} else
			err_quit("unexpected message type %d", ifm->ifm_type);
	}
}
