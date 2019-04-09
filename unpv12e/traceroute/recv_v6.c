#include	"trace.h"

/*
 * Return: -3 on timeout
 *		   -2 on ICMP time exceeded in transit (caller keeps going)
 *		   -1 on ICMP port unreachable (caller is done)
 *		 >= 0 return value is some other ICMP unreachable code
 */

int
recv_v6(int seq, struct timeval *tv)
{
#ifdef	IPV6
	int					hlen1, hlen2, icmp6len;
	ssize_t				n;
	socklen_t			len;
	struct ip6_hdr		*ip6, *hip6;
	struct icmp6_hdr	*icmp6;
	struct udphdr		*udp;

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

		ip6 = (struct ip6_hdr *) recvbuf;	/* start of IPv6 header */
		hlen1 = sizeof(struct ip6_hdr);
	
		icmp6 = (struct icmp6_hdr *) (recvbuf + hlen1); /* ICMP hdr */
		if ( (icmp6len = n - hlen1) < 8)
			err_quit("icmp6len (%d) < 8", icmp6len);
	
		if (icmp6->icmp6_type == ICMP6_TIME_EXCEEDED &&
			icmp6->icmp6_code == ICMP6_TIME_EXCEED_TRANSIT) {
			if (icmp6len < 8 + 40 + 8)
				err_quit("icmp6len (%d) < 8 + 40 + 8", icmp6len);

			hip6 = (struct ip6_hdr *) (recvbuf + hlen1 + 8);
			hlen2 = sizeof(struct ip6_hdr);
			udp = (struct udphdr *) (recvbuf + hlen1 + 8 + hlen2);
			if (hip6->ip6_nxt == IPPROTO_UDP &&
				udp->uh_sport == htons(sport) &&
				udp->uh_dport == htons(dport + seq))
				return(-2);		/* we hit an intermediate router */

		} else if (icmp6->icmp6_type == ICMP6_DST_UNREACH) {
			if (icmp6len < 8 + 40 + 8)
				err_quit("icmp6len (%d) < 8 + 40 + 8", icmp6len);

			hip6 = (struct ip6_hdr *) (recvbuf + hlen1 + 8);
			hlen2 = 40;
			udp = (struct udphdr *) (recvbuf + hlen1 + 8 + hlen2);
			if (hip6->ip6_nxt == IPPROTO_UDP &&
				udp->uh_sport == htons(sport) &&
				udp->uh_dport == htons(dport + seq)) {
				if (icmp6->icmp6_code == ICMP6_DST_UNREACH_NOPORT)
					return(-1);	/* have reached destination */
				else
					return(icmp6->icmp6_code);	/* 0, 1, 2, ... */
			}
		} else if (verbose) {
			printf(" (from %s: type = %d, code = %d)\n",
					Sock_ntop_host(pr->sarecv, pr->salen),
					icmp6->icmp6_type, icmp6->icmp6_code);
		}
		/* Some other ICMP error, recvfrom() again */
	}
#endif
}
