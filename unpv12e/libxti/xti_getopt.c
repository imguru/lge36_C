#include	"unpxti.h"

int
xti_getopt(int fd, int level, int name, void *optval, socklen_t *optlenp)
{
	int					rc, len;
	struct t_optmgmt	*req, *ret;
	struct t_opthdr		*topt;

	req = T_alloc(fd, T_OPTMGMT, T_ALL);
	ret = T_alloc(fd, T_OPTMGMT, T_ALL);
	if (req->opt.maxlen == 0)
		err_quit("xti_getopt: opt.maxlen == 0");

	topt = (struct t_opthdr *) req->opt.buf;
	topt->level = level;
	topt->name = name;
	topt->len = sizeof(struct t_opthdr);	/* just a t_opthdr{} */
	req->opt.len = topt->len;

	req->flags = T_CURRENT;
	if (t_optmgmt(fd, req, ret) < 0) {
		T_free(req, T_OPTMGMT);
		T_free(ret, T_OPTMGMT);
		return(-1);
	}
	rc = ret->flags;

	if (rc == T_SUCCESS || rc == T_READONLY) {
			/*4copy back value and length */
		topt = (struct t_opthdr *) ret->opt.buf;
		len = topt->len - sizeof(struct t_opthdr);
		len = min(len, *optlenp);
		memcpy(optval, topt+1, len);
		*optlenp = len;
	}

	T_free(req, T_OPTMGMT);
	T_free(ret, T_OPTMGMT);

	if (rc == T_SUCCESS || rc == T_READONLY)
		return(0);
	return(-1);		/* T_NOTSUPPORT */
}
