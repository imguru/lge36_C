#include	"unpxti.h"

int
xti_setopt(int fd, int level, int name, void *optval, socklen_t optlen)
{
	int					rc;
	struct t_optmgmt	*req, *ret;
	struct t_opthdr		*topt;

	req = T_alloc(fd, T_OPTMGMT, T_ALL);
	ret = T_alloc(fd, T_OPTMGMT, T_ALL);
	if (req->opt.maxlen == 0)
		err_quit("xti_setopt: req.opt.maxlen == 0");

	topt = (struct t_opthdr *) req->opt.buf;
	topt->level = level;
	topt->name = name;
	topt->len = sizeof(struct t_opthdr) + optlen;
	if (topt->len > req->opt.maxlen)
		err_quit("optlen too big");
	req->opt.len = topt->len;
	memcpy(topt+1, optval, optlen);	/* copy option value */

	req->flags = T_NEGOTIATE;
	if (t_optmgmt(fd, req, ret) < 0) {
		T_free(req, T_OPTMGMT);
		T_free(ret, T_OPTMGMT);
		return(-1);
	}
	rc = ret->flags;

	T_free(req, T_OPTMGMT);
	T_free(ret, T_OPTMGMT);

	if (rc == T_SUCCESS || rc == T_PARTSUCCESS)
		return(0);
	return(-1);		/* T_FAILURE, T_NOTSUPPORT, T_READONLY */
}
