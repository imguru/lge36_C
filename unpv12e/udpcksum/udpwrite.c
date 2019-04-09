#include	"udpcksum.h"

/*
 * "buf" points to an empty IP/UDP header,
 * followed by "ulen" bytes of user data.
 */

/* include udp_write */
void
udp_write(char *buf, int userlen)
{
	struct udpiphdr		*ui;
	struct ip			*ip;

		/* 4Fill in and checksum UDP header */
	ip = (struct ip *) buf;
	ui = (struct udpiphdr *) buf;
			/* 8add 8 to userlen for pseudo-header length */
	ui->ui_len = htons((u_short) (sizeof(struct udphdr) + userlen));
			/* 8then add 28 for IP datagram length */
	userlen += sizeof(struct udpiphdr);

	ui->ui_next = 0;
	ui->ui_prev = 0;
	ui->ui_x1 = 0;
	ui->ui_pr = IPPROTO_UDP;
	ui->ui_src.s_addr = ((struct sockaddr_in *) local)->sin_addr.s_addr;
	ui->ui_dst.s_addr = ((struct sockaddr_in *) dest)->sin_addr.s_addr;
	ui->ui_sport = ((struct sockaddr_in *) local)->sin_port;
	ui->ui_dport = ((struct sockaddr_in *) dest)->sin_port;
	ui->ui_ulen = ui->ui_len;
	ui->ui_sum = 0;
	if (zerosum == 0) {
# ifdef notdef		/* change to ifndef for Solaris 2.x, x < 6 */
		if ( (ui->ui_sum = in_cksum((u_short *) ui, userlen)) == 0)
			ui->ui_sum = 0xffff;
# else
		ui->ui_sum = ui->ui_len;
# endif
	}

		/* 4Fill in rest of IP header; */
		/* 4ip_output() calcuates & stores IP header checksum */
	ip->ip_v = IPVERSION;
	ip->ip_hl = sizeof(struct ip) >> 2;
	ip->ip_tos = 0;
#ifdef	linux
	ip->ip_len = htons(userlen);	/* network byte order */
#else
	ip->ip_len = userlen;			/* host byte order */
#endif
	ip->ip_id = 0;			/* let IP set this */
	ip->ip_off = 0;			/* frag offset, MF and DF flags */
	ip->ip_ttl = TTL_OUT;

	Sendto(rawfd, buf, userlen, 0, dest, destlen);
}
/* end udp_write */
