#include	"sntp.h"

const int	on = 1;		/* for setsockopt() flags */

int
main(int argc, char **argv)
{
	int					sockfd, port;
	socklen_t			salen;
	struct ifi_info		*ifi;
	struct sockaddr		*mcastsa, *wild;

	if (argc != 2)
		err_quit("usage: sntp <IPaddress>");

	sockfd = Udp_client(argv[1], "ntp", (void **) &mcastsa, &salen);
	port = sock_get_port(mcastsa, salen);
	Close(sockfd);

		/* 4obtain interface list and process each one */
	for (ifi = Get_ifi_info(mcastsa->sa_family, 1); ifi != NULL;
		 ifi = ifi->ifi_next) {
		bind_ubcast(ifi->ifi_addr, salen, port,
					ifi->ifi_myflags & IFI_ALIAS, 0);		/* unicast */

		if (ifi->ifi_flags & IFF_BROADCAST)
			bind_ubcast(ifi->ifi_brdaddr, salen, port,
						ifi->ifi_myflags & IFI_ALIAS, 1);	/* bcast */

#ifdef	MCAST
		if (ifi->ifi_flags & IFF_MULTICAST)
			bind_mcast(ifi->ifi_name, mcastsa, salen,
					   ifi->ifi_myflags & IFI_ALIAS);		/* mcast */
#endif
	}

	wild = Malloc(salen);	/* socket address struct for wildcard */
	memcpy(wild, mcastsa, salen);
	sock_set_wild(wild, salen);
	bind_ubcast(wild, salen, port, 0, 0);

	sntp_send();	/* send first queries */

	read_loop();	/* never returns */
}
