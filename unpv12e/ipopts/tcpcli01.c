#include	"unp.h"

int
main(int argc, char **argv)
{
	int					c, sockfd, len = 0;
	u_char				*ptr;
	struct addrinfo		*ai;

	if (argc < 2)
		err_quit("usage: tcpcli01 [ -[gG] <hostname> ... ] <hostname>");

	ptr = inet_srcrt_init();

	opterr = 0;		/* don't want getopt() writing to stderr */
	while ( (c = getopt(argc, argv, "g:G:")) != -1) {
		switch (c) {
		case 'g':			/* loose source route */
			len = inet_srcrt_add(optarg, 0);
			break;

		case 'G':			/* strict source route */
			len = inet_srcrt_add(optarg, 1);
			break;

		case '?':
			err_quit("unrecognized option: %c", c);
		}
	}

	if (optind != argc-1)
		err_quit("missing <hostname>");

	ai = Host_serv(argv[optind], SERV_PORT_STR, AF_INET, SOCK_STREAM);

	sockfd = Socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);

	if (len > 0) {
		len = inet_srcrt_add(argv[optind], 0);	/* dest at end */
		Setsockopt(sockfd, IPPROTO_IP, IP_OPTIONS, ptr, len);
		free(ptr);
	}

	Connect(sockfd, ai->ai_addr, ai->ai_addrlen);

	str_cli(stdin, sockfd);		/* do it all */

	exit(0);
}
