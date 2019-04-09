/* include loop1 */
#include	"sntp.h"

/* *INDENT-OFF* */
static int		 check_loop(struct sockaddr *, socklen_t);
static int		 check_dup(socklen_t);

static char		 buf1[MAXLINE], buf2[MAXLINE];
static char		*buf[2] = { buf1, buf2 };
struct sockaddr	*from[2];
static size_t	 nread[2] = { -1, -1 };
static int		 currb = 0, lastb = 1;
/* *INDENT-ON* */

void
read_loop(void)
{
	int				nsel, maxfd;
	Addrs			*aptr;
	fd_set			rset, allrset;
	socklen_t		len;
	struct timeval	now;

		/* 4allocate two socket address structures */
	from[0] = Malloc(addrs[0].addr_salen);
	from[1] = Malloc(addrs[0].addr_salen);

	maxfd = -1;
	for (aptr = &addrs[0]; aptr < &addrs[naddrs]; aptr++) {
		FD_SET(aptr->addr_fd, &allrset);
		if (aptr->addr_fd > maxfd)
			maxfd = aptr->addr_fd;
	}
/* end loop1 */

/* include loop2 */
	for ( ; ; ) {
		rset = allrset;
		nsel = Select(maxfd+1, &rset, NULL, NULL, NULL);

		Gettimeofday(&now, NULL);	/* get time when select returns */

		for (aptr = &addrs[0]; aptr < &addrs[naddrs]; aptr++) {
			if (FD_ISSET(aptr->addr_fd, &rset)) {
				len = aptr->addr_salen;
				nread[currb] = recvfrom(aptr->addr_fd,
										buf[currb], MAXLINE, 0,
										from[currb], &len);
				if (aptr->addr_flags & ADDR_MCAST) {
					printf("%d bytes from %s", nread[currb],
							Sock_ntop(from[currb], aptr->addr_salen));
					printf(" multicast to %s", aptr->addr_ifname);

				} else if (aptr->addr_flags & ADDR_BCAST) {
					printf("%d bytes from %s", nread[currb],
							Sock_ntop(from[currb], aptr->addr_salen));
					printf(" broadcast to %s",
							Sock_ntop(aptr->addr_sa, aptr->addr_salen));

				} else {
					printf("%d bytes from %s", nread[currb],
							Sock_ntop(from[currb], aptr->addr_salen));
					printf(" to %s",
							Sock_ntop(aptr->addr_sa, aptr->addr_salen));
				}

				if (check_loop(from[currb], aptr->addr_salen)) {
					printf(" (ignored)\n");
					continue;		/* it's one of ours, looped back */
				}
				if (check_dup(aptr->addr_salen)) {
					printf(" (dup)\n");
					continue;		/* it's a duplicate */
				}

				sntp_proc(buf[lastb], nread[lastb], &now);

				if (--nsel <= 0)
					break;		/* all done with selectable descriptors */
			}
		}
	}
}
/* end loop2 */

/* include check_loop */
int
check_loop(struct sockaddr *sa, socklen_t salen)
{
	Addrs	*aptr;

	for (aptr = &addrs[0]; aptr < &addrs[naddrs]; aptr++) {
		if (sock_cmp_addr(sa, aptr->addr_sa, salen) == 0)
			return(1);		/* it is one of our addresses */
	}
	return(0);
}
/* end check_loop */

/* include check_dup */
int
check_dup(socklen_t salen)
{
	int		temp;

	if (nread[currb] == nread[lastb] &&
		memcmp(from[currb], from[lastb], salen) == 0 &&
		memcmp(buf[currb], buf[lastb], nread[currb]) == 0) {
			return(1);	/* it is a duplicate */
	}

	temp = currb;	/* swap currb and lastb */
	currb = lastb;
	lastb = temp;
	return(0);
}
/* end check_dup */
