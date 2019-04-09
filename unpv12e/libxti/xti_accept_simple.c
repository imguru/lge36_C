#include	"unpxti.h"

int
xti_accept(int listenfd, struct netbuf *cliaddr, int rdwr)
{
	int				connfd;
	u_int			n;
	struct t_call	*tcallp;

	tcallp = T_alloc(listenfd, T_CALL, T_ALL);
	
	T_listen(listenfd, tcallp);		/* blocks */

		/*4following assumes caller called tcp_listen() */
	connfd = T_open(xti_serv_dev, O_RDWR, NULL);
	T_bind(connfd, NULL, NULL);
	T_accept(listenfd, connfd, tcallp);

	if (rdwr)
		Xti_rdwr(connfd);

	if (cliaddr) {		/* return client's protocol address */
		n = min(cliaddr->maxlen, tcallp->addr.len);
		memcpy(cliaddr->buf, tcallp->addr.buf, n);
		cliaddr->len = n;
	}

	T_free(tcallp, T_CALL);
	return(connfd);
}
