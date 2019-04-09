#include	"trace.h"

/*
 * Return: -3 on timeout
 *		   -2 on ICMP time exceeded in transit (caller keeps going)
 *		   -1 on ICMP port unreachable (caller is done)
 *		 >= 0 return value is some other ICMP unreachable code
 */

int
recv_v4(int seq, struct timeval *tv)
{
	int				hlen1, hlen2, icmplen;
	socklen_t		len;
	ssize_t			n;
	struct ip		*ip, *hip;
	struct icmp		*icmp;
	struct udphdr	*udp;

	alarm(3);
	for ( ; ; ) {
		len = pr->salen;
		n = recvfrom(recvfd, recvbuf, sizeof(recvbuf), 0, pr->sarecv, &len);
		if (n < 0) {
			if (errno == EINTR)
				return(-3);		/* alarm expired */
			else
				err_sys("recvfrom error");
		}
		Gettimeofday(tv, NULL);		/* get time of packet arrival */

		ip = (struct ip *) recvbuf;	/* start of IP header */
		hlen1 = ip->ip_hl << 2;		/* length of IP header */
	
		icmp = (struct icmp *) (recvbuf + hlen1); /* start of ICMP header */
		if ( (icmplen = n - hlen1) < 8)
			err_quit("icmplen (%d) < 8", icmplen);
	
		if (icmp->icmp_type == ICMP_TIMXCEED &&
			icmp->icmp_code == ICMP_TIMXCEED_INTRANS) {
			if (icmplen < 8 + 20 + 8)
				err_quit("icmplen (%d) < 8 + 20 + 8", icmplen);

			hip = (struct ip *) (recvbuf + hlen1 + 8);
			hlen2 = hip->ip_hl << 2;
			udp = (struct udphdr *) (recvbuf + hlen1 + 8 + hlen2);
 			if (hip->ip_p == IPPROTO_UDP &&
				udp->uh_sport == htons(sport) &&
				udp->uh_dport == htons(dport + seq))
				return(-2);		/* we hit an intermediate router */

		} else if (icmp->icmp_type == ICMP_UNREACH) {
			if (icmplen < 8 + 20 + 8)
				err_quit("icmplen (%d) < 8 + 20 + 8", icmplen);

			hip = (struct ip *) (recvbuf + hlen1 + 8);
			hlen2 = hip->ip_hl << 2;
			udp = (struct udphdr *) (recvbuf + hlen1 + 8 + hlen2);
 			if (hip->ip_p == IPPROTO_UDP &&
				udp->uh_sport == htons(sport) &&
				udp->uh_dport == htons(dport + seq)) {
				if (icmp->icmp_code == ICMP_UNREACH_PORT)
					return(-1);	/* have reached destination */
				else
					return(icmp->icmp_code);	/* 0, 1, 2, ... */
			}
		} else if (verbose) {
			printf(" (from %s: type = %d, code = %d)\n",
					Sock_ntop_host(pr->sarecv, pr->salen),
					icmp->icmp_type, icmp->icmp_code);
		}
		/* Some other ICMP error, recvfrom() again */
	}
}
