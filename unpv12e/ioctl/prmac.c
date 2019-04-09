#include	"unp.h"
#include	<net/if_arp.h>

int
main(int argc, char **argv)
{
	int					family, sockfd;
	char				str[INET6_ADDRSTRLEN];
	char				**pptr;
	unsigned char		*ptr;
	struct arpreq		arpreq;
	struct sockaddr_in	*sin;

	pptr = my_addrs(&family);
	for ( ; *pptr != NULL; pptr++) {
		printf("%s: ", Inet_ntop(family, *pptr, str, sizeof(str)));
		switch (family) {
		case AF_INET:
			sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

			sin = (struct sockaddr_in *) &arpreq.arp_pa;
			bzero(sin, sizeof(struct sockaddr_in));
			sin->sin_family = AF_INET;
			memcpy(&sin->sin_addr, *pptr, sizeof(struct in_addr));

			Ioctl(sockfd, SIOCGARP, &arpreq);

			ptr = &arpreq.arp_ha.sa_data[0];
			printf("%x:%x:%x:%x:%x:%x\n", *ptr, *(ptr+1),
				   *(ptr+2), *(ptr+3), *(ptr+4), *(ptr+5));
			break;

		default:
			err_quit("unsupported address family: %d", family);
		}
	}
	exit(0);
}
