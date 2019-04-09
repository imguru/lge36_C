/*
 * XTI wrapper functions.
 */

#include	"unpxti.h"

#include	<stdarg.h>		/* ANSI C header file */
#include	<syslog.h>		/* for syslog() */

extern int		daemon_proc;	/* set nonzero by daemon_init() */

/*
 * First the err_xti() function.  We don't want it in ../lib/error.c,
 * as some environments may not DefinE t_errno.
 */

static void	err_xti_doit(int, int, const char *, va_list);

void
err_xti(const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
	err_xti_doit(1, LOG_ERR, fmt, ap);
	va_end(ap);
	exit(1);
}

void
err_xti_ret(const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
	err_xti_doit(1, LOG_INFO, fmt, ap);
	va_end(ap);
	return;
}

static void
err_xti_doit(int errnoflag, int level, const char *fmt, va_list ap)
{
	int		errno_save, n;
	char	buf[MAXLINE];

	errno_save = errno;		/* value caller might want printed */
#ifdef	HAVE_VSNPRINTF
	vsnprintf(buf, sizeof(buf), fmt, ap);
#else
	vsprintf(buf, fmt, ap);
#endif
	n = strlen(buf);
	if (errnoflag) {
		snprintf(buf+n, sizeof(buf)-n, ": %s", t_strerror(t_errno));
		n = strlen(buf);
		if (t_errno == TSYSERR)
			snprintf(buf+n, sizeof(buf)-n, ": %s", strerror(errno_save));
	}
	strcat(buf, "\n");

	if (daemon_proc) {
		syslog(level, buf);
	} else {
		fflush(stdout);		/* in case stdout and stderr are the same */
		fputs(buf, stderr);
		fflush(stderr);
	}
	return;
}

int
Getmsg(int fd, struct strbuf *ctlp, struct strbuf *datap, int *flagsp)
{
	int		rc;

	if ( (rc = getmsg(fd, ctlp, datap, flagsp)) == -1)
		err_sys("getmsg error");
	return(rc);		/* can be 0, MORECTL and/or MOREDATA */
}

void
Putmsg(int fd, const struct strbuf *ctlp, const struct strbuf *datap, int flags)
{
	if (putmsg(fd, ctlp, datap, flags) == -1)
		err_sys("putmsg error");
}

#ifdef	HAVE_NETCONFIG_H
void *
Setnetconfig(void)
{
	void	*handle;

	if ( (handle = setnetconfig()) == NULL)
		err_quit("setnetconfig error");
	return(handle);
}
#endif

#ifdef	HAVE_NETCONFIG_H
void *
Setnetpath(void)
{
	void	*handle;

	if ( (handle = setnetpath()) == NULL)
		err_quit("setnetpath error");
	return(handle);
}
#endif

int
T_accept(int fd, int resfd, struct t_call *call)
{
	int		n;

	if ( (n = t_accept(fd, resfd, call)) == -1)
		err_xti("t_accept error");

	return(n);
}

void *
T_alloc(int fd, int structtype, int fields)
{
	void	*ptr;

	if ( (ptr = t_alloc(fd, structtype, fields)) == NULL)
		err_xti("t_alloc error");
	return(ptr);
}

void
T_bind(int fd, const struct t_bind *req, struct t_bind *ret)
{
	if (t_bind(fd, req, ret) == -1)
		err_xti("t_bind error");
}

void
T_close(int fd)
{
	if (t_close(fd) == -1)
		err_xti("t_close error");
}

void
T_connect(int fd, const struct t_call *sndcall, struct t_call *rcvcall)
{
	if (t_connect(fd, sndcall, rcvcall) == -1)
		err_xti("t_connect error");
}

void
T_free(void *ptr, int structtype)
{
	if (t_free(ptr, structtype) == -1)
		err_xti("t_free error");
}

void
T_getprotaddr(int fd, struct t_bind *bound, struct t_bind *peer)
{
	if (t_getprotaddr(fd, bound, peer) == -1)
		err_xti("t_getprotaddr error");
}

int
T_getstate(int fd)
{
	int		n;

	if ( (n = t_getstate(fd)) == -1)
		err_xti("t_getstate error");

	return(n);
}

void
T_listen(int fd, struct t_call *call)
{
	if (t_listen(fd, call) == -1)
		err_xti("t_listen error");
}

int
T_look(int fd)
{
	int		n;

	if ( (n = t_look(fd)) == -1)
		err_xti("t_look error");

	return(n);
}

int
T_open(const char *name, int oflag, struct t_info *info)
{
	int		n;

	if ( (n = t_open(name, oflag, info)) == -1)
		err_xti("t_open error for %s", name ? name : "(null ptr passed)");

	return(n);
}

void
T_optmgmt(int fd, const struct t_optmgmt *req, struct t_optmgmt *ret)
{
	if (t_optmgmt(fd, req, ret) == -1)
		err_xti("t_optmgmt error");
}

int
T_rcv(int fd, void *buf, unsigned int nbytes, int *flags)
{
	int		n;

	if ( (n = t_rcv(fd, buf, nbytes, flags)) == -1)
		err_xti("t_rcv error");

	return(n);
}

void
T_rcvdis(int fd, struct t_discon *discon)
{
	if (t_rcvdis(fd, discon) == -1)
		err_xti("t_rcvdis error");
}

void
T_rcvrel(int fd)
{
	if (t_rcvrel(fd) == -1)
		err_xti("t_rcvrel error");
}

void
T_rcvudata(int fd, struct t_unitdata *ud, int *flags)
{
	if (t_rcvudata(fd, ud, flags) == -1)
		err_xti("t_rcvudata error");
}

void
T_rcvuderr(int fd, struct t_uderr *ud)
{
	if (t_rcvuderr(fd, ud) == -1)
		err_xti("t_rcvudata error");
}

void
T_snd(int fd, void *buf, unsigned int nbytes, int flags)
{
	int		n;

	if ( (n = t_snd(fd, buf, nbytes, flags)) != nbytes)
		err_xti("t_snd error");
}

void
T_sndrel(int fd)
{
	if (t_sndrel(fd) == -1)
		err_xti("t_sndrel error");
}

void
T_sndudata(int fd, struct t_unitdata *ud)
{
	if (t_sndudata(fd, ud) == -1)
		err_xti("t_sndudata error");
}

#ifdef	HAVE_NETCONFIG_H
char *
Taddr2uaddr(struct netconfig *ncp, struct netbuf *np)
{
	char	*ptr;

	if ( (ptr = taddr2uaddr(ncp, np)) == NULL)
		return("(unknown host)");
	return(ptr);
}
#endif

#ifdef	HAVE_NETDIR_H
int
Xti_accept(int listenfd, struct netbuf *np, int rdwr)
{
	int		connfd;

	if ( (connfd = xti_accept(listenfd, np, rdwr)) == -1)
		err_xti("xti_accept error");
	return(connfd);
}
#endif

void
Xti_getopt(int fd, int level, int name, void *optval, socklen_t *optlenp)
{
	if (xti_getopt(fd, level, name, optval, optlenp) == -1)
		err_xti("xti_getopt error");
}

char *
Xti_ntop(const struct netbuf *np)
{
	char	*ptr;

	if ( (ptr = xti_ntop(np)) == NULL)
		err_quit("xti_ntop error");
	return(ptr);
}

char *
Xti_ntop_host(const struct netbuf *np)
{
	char	*ptr;

	if ( (ptr = xti_ntop_host(np)) == NULL)
		err_quit("xti_ntop_host error");
	return(ptr);
}

void
Xti_rdwr(int fd)
{
	if (xti_rdwr(fd) == -1)
		err_sys("xti_rdwr error");
}

void
Xti_setopt(int fd, int level, int name, void *optval, socklen_t optlen)
{
	if (xti_setopt(fd, level, name, optval, optlen) == -1)
		err_xti("xti_setopt error");
}
