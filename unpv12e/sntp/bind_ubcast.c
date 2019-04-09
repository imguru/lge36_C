#include	"sntp.h"

void
bind_ubcast(struct sockaddr *sabind, socklen_t salen, int port,
			int alias, int bcast)
{
	int		i, fd;

		/* 4first see if we've already bound this address */
	for (i = 0; i < naddrs; i++) {
		if (sock_cmp_addr(addrs[i].addr_sa, sabind, salen) == 0)
			return;
	}

	fd = Socket(sabind->sa_family, SOCK_DGRAM, 0);

	sock_set_port(sabind, salen, port);

	Setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	printf("binding %s\n", Sock_ntop(sabind, salen));
	if (bind(fd, sabind, salen) < 0) {
		if (errno == EADDRINUSE) {
			printf("  (address already in use)\n");
			close(fd);
			return;
		} else
			err_sys("bind error");
	}

	addrs[naddrs].addr_sa = sabind;	/* save ptr to sockaddr{} */
	addrs[naddrs].addr_salen = salen;
	addrs[naddrs].addr_fd = fd;
	if (bcast)
		addrs[naddrs].addr_flags = ADDR_BCAST;
	naddrs++;
}
