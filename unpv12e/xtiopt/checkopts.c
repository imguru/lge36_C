/* include checkopts1 */
/* *INDENT-OFF* */
#include	"unpxti.h"

struct xti_opts {
  char			*opt_str;
  t_uscalar_t	 opt_level;
  t_uscalar_t	 opt_name;
  char   	  *(*opt_val_str)(struct t_opthdr *);
} xti_opts[] = {
	"XTI_DEBUG",		XTI_GENERIC,	XTI_DEBUG,		xti_str_uscalard,
	"XTI_LINGER",		XTI_GENERIC,	XTI_LINGER,		xti_str_linger,
	"XTI_RCVBUF",		XTI_GENERIC,	XTI_RCVBUF,		xti_str_uscalard,
	"XTI_RCVLOWAT",		XTI_GENERIC,	XTI_RCVLOWAT,	xti_str_uscalard,
	"XTI_SNDBUF",		XTI_GENERIC,	XTI_SNDBUF,		xti_str_uscalard,
	"XTI_SNDLOWAT",		XTI_GENERIC,	XTI_SNDLOWAT,	xti_str_uscalard,
	"T_IP_BROADCAST",	T_INET_IP,		T_IP_BROADCAST,	xti_str_uiyn,
	"T_IP_DONTROUTE",	T_INET_IP,		T_IP_DONTROUTE,	xti_str_uiyn,
	"T_IP_OPTIONS",		T_INET_IP,		T_IP_OPTIONS,	xti_str_uchard,
	"T_IP_REUSEADDR",	T_INET_IP,		T_IP_REUSEADDR,	xti_str_uiyn,
	"T_IP_TOS",			T_INET_IP,		T_IP_TOS,		xti_str_ucharx,
	"T_IP_TTL",			T_INET_IP,		T_IP_TTL,		xti_str_uchard,
	"T_TCP_KEEPALIVE",	T_INET_TCP,		T_TCP_KEEPALIVE,xti_str_kpalive,
	"T_TCP_MAXSEG",		T_INET_TCP,		T_TCP_MAXSEG,	xti_str_uscalard,
	"T_TCP_NODELAY",	T_INET_TCP,		T_TCP_NODELAY,	xti_str_usyn,
	"T_UDP_CHECKSUM",	T_INET_UDP,		T_UDP_CHECKSUM,	xti_str_usyn,
	NULL,				0,				0,				NULL
};
/* *INDENT-ON* */
/* end checkopts1 */

/* include checkopts2 */
int
main(int argc, char **argv)
{
	int					fd;
	struct t_opthdr		*topt;
	struct t_optmgmt	*req, *ret;
	struct xti_opts		*ptr;

	if (argc != 2)
		err_quit("usage: checkopts <device>");

	fd = T_open(argv[1], O_RDWR, NULL);
	T_bind(fd, NULL, NULL);

	req = T_alloc(fd, T_OPTMGMT, T_ALL);
	ret = T_alloc(fd, T_OPTMGMT, T_ALL);

	for (ptr = xti_opts; ptr->opt_str != NULL; ptr++) {
		topt = (struct t_opthdr *) req->opt.buf;
		topt->level = ptr->opt_level;
		topt->name = ptr->opt_name;
		topt->len = sizeof(struct t_opthdr);
		req->opt.len = topt->len;
	
		req->flags = T_CHECK;
		printf("%s: ", ptr->opt_str);
		if (t_optmgmt(fd, req, ret) < 0) {
			err_xti_ret("t_optmgmt error");
		} else {
			topt = (struct t_opthdr *) ret->opt.buf;
			printf("%s", xti_str_flags(topt->status));

			if (topt->status == T_SUCCESS || topt->status == T_READONLY) {
				req->flags = T_DEFAULT;
				if (t_optmgmt(fd, req, ret) < 0) {
					err_xti_ret("t_optmgmt error for T_DEFAULT");
				} else {
					topt = (struct t_opthdr *) ret->opt.buf;
					printf(", default = %s", (*ptr->opt_val_str)(topt));
				}
			}
			printf("\n");
		}
	}
	exit(0);
}
/* end checkopts2 */
