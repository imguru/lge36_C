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
		printf("datagram from %s\n", Xti_ntop(&tud->addr));

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		tud->udata.len = strlen(buff);

		topt = (struct t_opthdr *) tud->opt.buf;
		topt->level = T_INET_IP;
		topt->name = T_IP_TTL;
		topt->len = sizeof(struct t_opthdr) + sizeof(u_char);
		tud->opt.len = topt->len;
		*((u_char *) (topt + 1)) = 137;

        T_sndudata(tfd, tud);
	}
}
