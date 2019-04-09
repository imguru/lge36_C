#include	"unpxti.h"
#include	<time.h>

int
main(int argc, char **argv)
{
	int					tfd, flags;
	char				buff[MAXLINE];
	time_t				ticks;
	struct t_opthdr		*topt;
	struct t_unitdata	*tud;

	if (argc == 2)
		tfd = Udp_server(NULL, argv[1], NULL);
	else if (argc == 3)
		tfd = Udp_server(argv[1], argv[2], NULL);
	else
		err_quit("usage: daytimeudpsrv [ <host> ] <service or port>");

	tud = T_alloc(tfd, T_UNITDATA, T_ALL);

	for ( ; ; ) {
		tud->udata.maxlen = MAXLINE;
		tud->udata.buf = buff;
		T_rcvudata(tfd, tud, &flags);
		printf("datagram from %s, opt maxlen = %d, opt len = %d\n",
			   Xti_ntop(&tud->addr), tud->opt.maxlen, tud->opt.len);

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		tud->udata.len = strlen(buff);

		topt = (struct t_opthdr *) tud->opt.buf;
		topt->level = T_INET_IP;
		topt->name = T_IP_TTL;
		topt->len = sizeof(struct t_opthdr) + sizeof(u_char);
		*((u_char *) (topt + 1)) = 137;

		topt = OPT_NEXTHDR(tud->opt.buf, tud->opt.maxlen, topt);
		topt->level = T_INET_IP;
		topt->name = T_IP_TOS;
		topt->len = sizeof(struct t_opthdr) + sizeof(u_char);
		*((u_char *) (topt + 1)) = SET_TOS(T_ROUTINE, T_LDELAY);

		topt = OPT_NEXTHDR(tud->opt.buf, tud->opt.maxlen, topt);
		topt->level = T_INET_UDP;
		topt->name = T_UDP_CHECKSUM;
		topt->len = sizeof(struct t_opthdr) + sizeof(u_long);
		*((u_long *) (topt + 1)) = T_NO;

		topt = OPT_NEXTHDR(tud->opt.buf, tud->opt.maxlen, topt);
		tud->opt.len = (char *)topt - (char *)tud->opt.buf;

        T_sndudata(tfd, tud);
	}
}
