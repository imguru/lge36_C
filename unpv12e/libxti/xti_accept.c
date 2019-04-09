/* include xti_accept1 */
#include	"unpxti.h"

static int		ncli = -1, ndisconn;
static struct cli {
  int			connfd;	/* connected fd or -1 if disconnected */
  int			count;
  struct t_call	*tcallp;/* ptr to t_alloc'ed structure */
} *cli;					/* cli[0], cli[1], ..., cli[ncli-1] are in use */

int
xti_accept(int listenfd, struct netbuf *cliaddr, int rdwr)
{
	int				i, event;
	u_int			n;
	char			*ptr;
	struct t_discon	tdiscon;

	if (ncli == -1) {		/* initialize first time through */
		if (cli != NULL)
			err_quit("already initialized");
		if ( (ptr = getenv("LISTENQ")) != NULL)
			n = atoi(ptr);
		else
			n = LISTENQ;
		cli = Calloc(n, sizeof(struct cli));
		for (i = 0; i < n; i++)
			cli[i].tcallp = T_alloc(listenfd, T_CALL, T_ALL);
		ncli = 0;
	}
/* end xti_accept1 */

/* include xti_accept2 */
	for ( ; ; ) {
		if (ncli == 0) {	/* need to wait for a connection */
			T_listen(listenfd, cli[ncli].tcallp);	/* block here */
	
				/* 4following assumes caller called tcp_listen() */
			cli[ncli].connfd = T_open(xti_serv_dev, O_RDWR, NULL);
			T_bind(cli[ncli].connfd, NULL, NULL);
			cli[ncli].count++;
			ncli++;
		}
	
		if (t_accept(listenfd, cli[ncli-1].connfd,
					 cli[ncli-1].tcallp) == 0) {
			ncli--;			/* success */
			if (rdwr)
				Xti_rdwr(cli[ncli].connfd);
		
			if (cliaddr) {		/* return client's protocol address */
				n = min(cliaddr->maxlen, cli[ncli].tcallp->addr.len);
				memcpy(cliaddr->buf, cli[ncli].tcallp->addr.buf, n);
				cliaddr->len = n;
			}
			return(cli[ncli].connfd);
		
		} else if (t_errno == TLOOK) {
			if ( (event = T_look(listenfd)) == T_LISTEN) {
				T_listen(listenfd, cli[ncli].tcallp);	/* won't block */
				cli[ncli].connfd = T_open(xti_serv_dev, O_RDWR, NULL);
				T_bind(cli[ncli].connfd, NULL, NULL);
				cli[ncli].count++;
				ncli++;
	
			} else if (event == T_DISCONNECT) {
				T_rcvdis(listenfd, &tdiscon);
				for (i = 0; i < ncli; i++) {
					if (cli[i].tcallp->sequence == tdiscon.sequence) {
						T_close(cli[i].connfd);
#ifdef	NOTDEF
						printf("disconnect received from %s\n",
								Xti_ntop(&cli[i].tcallp->addr));
#endif
						ndisconn++;
						ncli--;
						if ( (n = ncli - i) > 0)
							memmove(&cli[i], &cli[i+1],
									n*sizeof(struct cli));
						break;
					}
				}
			} else
				err_quit("unexpected t_look event %d", event);
		} else
			err_xti("unexpected t_accept error");
	}
}
/* end xti_accept2 */

void
xti_accept_dump(void)
{
	int		i, total;

	for (i = total = 0; ; i++) {
		if (cli[i].count == 0)
			break;
		printf("%2d %5d\n", i, cli[i].count);
		total += cli[i].count;
	}
	printf("#disconnects = %d\n", ndisconn);
	printf("total = %d\n", total);
}
