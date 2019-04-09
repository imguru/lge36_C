/* include sig_alrm */
#include	"udpcksum.h"
#include	<setjmp.h>

static sigjmp_buf	jmpbuf;
static int			canjump;

void
sig_alrm(int signo)
{
	if (canjump == 0)
		return;
	siglongjmp(jmpbuf, 1);
}
/* end sig_alrm */

/*
 * Build a DNS A query for "a.root-servers.net" and write it to
 * the raw socket.
 */

/* include send_dns_query */
void
send_dns_query(void)
{
	size_t		nbytes;
	char		buf[sizeof(struct udpiphdr) + 100], *ptr;
	short		one;

	ptr = buf + sizeof(struct udpiphdr);/* leave room for IP/UDP headers */

	*((u_short *) ptr) = htons(1234);	/* identification */
	ptr += 2;
	*((u_short *) ptr) = htons(0x0);	/* flags */
	ptr += 2;
	*((u_short *) ptr) = htons(1);		/* #questions */
	ptr += 2;
	*((u_short *) ptr) = 0;				/* #answer RRs */
	ptr += 2;
	*((u_short *) ptr) = 0;				/* #authority RRs */
	ptr += 2;
	*((u_short *) ptr) = 0;				/* #additional RRs */
	ptr += 2;

	memcpy(ptr, "\001a\014root-servers\003net\000", 20);
	ptr += 20;
	one = htons(1);
	memcpy(ptr, &one, 2);				/* query type = A */
	ptr += 2;
	memcpy(ptr, &one, 2);				/* query class = 1 (IP addr) */
	ptr += 2;

	nbytes = 36;
	udp_write(buf, nbytes);
	if (verbose)
		printf("sent: %d bytes of data\n", nbytes);
}
/* end send_dns_query */

/* include test_udp */
void
test_udp(void)
{
	volatile int	nsent = 0, timeout = 3;
	struct udpiphdr	*ui;

	Signal(SIGALRM, sig_alrm);

	if (sigsetjmp(jmpbuf, 1)) {
		if (nsent >= 3)
			err_quit("no response");
		printf("timeout\n");
		timeout *= 2;		/* exponential backoff: 3, 6, 12 */
	}
	canjump = 1;	/* siglongjmp is now OK */

	send_dns_query();
	nsent++;

	alarm(timeout);
	ui = udp_read();
	canjump = 0;
	alarm(0);

	if (ui->ui_sum == 0)
		printf("UDP checksums off\n");
	else
		printf("UDP checksums on\n");
	if (verbose)
		printf("recevied UDP checksum = %x\n", ui->ui_sum);
}
/* end test_udp */
