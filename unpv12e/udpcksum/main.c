/* include main1 */
#include	"udpcksum.h"

			/* DefinE global variables */
struct sockaddr	*dest, *local;
socklen_t		destlen, locallen;

int		datalink;		/* from pcap_datalink(), in <net/bpf.h> */
char   *device;			/* pcap device */
int		fddipad;		/* HACK; for libpcap if FDDI defined */
pcap_t *pd;				/* packet capture struct pointer */
int		rawfd;			/* raw socket to write on */
int		snaplen = 200;	/* amount of data to capture */
int		verbose;
int		zerosum;		/* send UDP query with no checksum */

static void	usage(const char *);

int
main(int argc, char *argv[])
{
	int				c, on=1;
	char			*ptr, localname[1024], *localport;
	struct addrinfo	*aip;

	if (argc < 2)
		usage("");

	/*
	 * Need local IP address for source IP address for UDP datagrams.
	 * Can't specify 0 and let IP choose, as we need to know it for
	 * the pseudo-header to calculate the UDP checksum.
	 * Both localname and localport can be overridden by -l option.
	 */

	if (gethostname(localname, sizeof(localname)) < 0)
		err_sys("gethostname error");
	localport = LOCALPORT;
/* end main1 */

/* include main2 */
	opterr = 0;		/* don't want getopt() writing to stderr */
	while ( (c = getopt(argc, argv, "0i:l:v")) != -1) {
		switch (c) {

		case '0':
			zerosum = 1;
			break;

		case 'i':
			device = optarg;			/* pcap device */
			break;

		case 'l':			/* local IP address and port#: a.b.c.d.p */
			if ( (ptr = strrchr(optarg, '.')) == NULL)
				usage("invalid -l option");

			*ptr++ = 0;					/* null replaces final period */
			localport = ptr;			/* service name or port number */
			strncpy(localname, optarg, sizeof(localname));
			break;

		case 'v':
			verbose = 1;
			break;

		case '?':
			usage("unrecognized option");
		}
	}
/* end main2 */
/* include main3 */
	if (optind != argc-2)
		usage("missing <host> and/or <serv>");

		/* 4convert destination name and service */
	aip = host_serv(argv[optind], argv[optind+1], AF_INET, SOCK_DGRAM);
	dest = aip->ai_addr;		/* don't freeaddrinfo() */
	destlen = aip->ai_addrlen;

		/* 4convert local name and service */
	aip = host_serv(localname, localport, AF_INET, SOCK_DGRAM);
	local = aip->ai_addr;		/* don't freeaddrinfo() */
	locallen = aip->ai_addrlen;

	/*
	 * Need a raw socket to write our own IP datagrams to.
	 * Process must have superuser privileges to create this socket.
	 * Also must set IP_HDRINCL so we can write our own IP headers.
	 */

	rawfd = Socket(dest->sa_family, SOCK_RAW, 0);

	Setsockopt(rawfd, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on));

	open_pcap();		/* open packet capture device */

	setuid(getuid());	/* don't need superuser privileges any more */

	Signal(SIGTERM, cleanup);
	Signal(SIGINT, cleanup);
	Signal(SIGHUP, cleanup);

	test_udp();

	cleanup(0);
}
/* end main3 */

static void
usage(const char *msg)
{
	err_msg(
"usage: testudp [ options ] <host> <serv>\n"
"options: -0    send UDP datagram with checksum set to 0"
"         -i s  packet capture device\n"
"         -l a.b.c.d.p  local IP=a.b.c.d, local port=p\n"
"         -v    verbose output"
);

	if (msg[0] != 0)
		err_quit("%s", msg);
	exit(1);
}
