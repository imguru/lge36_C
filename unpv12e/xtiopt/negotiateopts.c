#include	"unpxti.h"

static	struct t_optmgmt	*req, *ret;

char *
xti_flag_str(long flag)
{
	static char	str[128];

	if (flag == T_SUCCESS)			return("T_SUCCESS");
	else if (flag == T_FAILURE)		return("T_FAILURE");
	else if (flag == T_NOTSUPPORT)	return("T_NOTSUPPORT");
	else if (flag == T_READONLY)	return("T_READONLY");
	else if (flag == T_PARTSUCCESS)	return("T_PARTSUCCESS");
	snprintf(str, sizeof(str), "unknown value: %ld", flag);
	return(str);
}

void
xti_set_uchar_opt(int fd, const char *str, u_long level, u_long name, u_int val)
{
	struct t_opthdr		*topt;

		/* first check that option is supported */
	topt = (struct t_opthdr *) req->opt.buf;
	topt->level = level;
	topt->name = name;
	topt->len = sizeof(struct t_opthdr);	/* just the header, no value */
	req->opt.len = topt->len;
	
	req->flags = T_CHECK;
	printf("%s: check: ", str);
	if (t_optmgmt(fd, req, ret) == -1) {
		printf("t_optmgmt error %d", t_errno);
	} else {
		if (ret->opt.len >= sizeof(struct t_opthdr)) {
			topt = (struct t_opthdr *) ret->opt.buf;
			printf("%s", xti_flag_str(topt->status));
		} else
			printf("*ret->opt.len = %d", ret->opt.len);
	}

		/* get default value of option */
		/* ret is "const", so it was not changed by t_optmgmt() */
	topt = (struct t_opthdr *) req->opt.buf;
	topt->status = 0;
	req->flags = T_DEFAULT;
	printf("; default: ");
	if (t_optmgmt(fd, req, ret) == -1) {
		printf("t_optmgmt error %d", t_errno);
	} else {
		topt = (struct t_opthdr *) ret->opt.buf;
		printf("(ret->opt.len = %d, len = %d) ", ret->opt.len, topt->len);
		if (topt->status == T_SUCCESS || topt->status == T_READONLY)
			printf("%u", *((u_char *) (topt + 1)));
		else
			printf("status = %ld", topt->status);
	}

		/* now change value */
	topt = (struct t_opthdr *) req->opt.buf;
	topt->status = 0;
	topt->len += sizeof(u_long);
	req->opt.len = topt->len;
	*((u_long *) (topt + 1)) = val;
	req->flags = T_NEGOTIATE;
	printf("; negotiated: ");
	if (t_optmgmt(fd, req, ret) == -1) {
		printf("t_optmgmt error %d", t_errno);
	} else {
		topt = (struct t_opthdr *) ret->opt.buf;
		if (topt->status == T_SUCCESS)
			printf("T_SUCCESS");
		else if (topt->status == T_PARTSUCCESS)
			printf("T_PARTSUCCESS");
		else if (topt->status == T_READONLY)
			printf("T_READONLY");
		else if (topt->status == T_FAILURE)
			printf("T_FAILURE");
		else if (topt->status == T_NOTSUPPORT)
			printf("T_NOTSUPPORT");
		else
			printf("status = %ld\n", topt->status);
	}

	topt = (struct t_opthdr *) req->opt.buf;
	topt->len -= sizeof(u_long);
	req->opt.len = topt->len;
	req->flags = T_CURRENT;
	printf("; current: ");
	if (t_optmgmt(fd, req, ret) == -1) {
		printf("t_optmgmt error %d", t_errno);
	} else {
		topt = (struct t_opthdr *) ret->opt.buf;
		if (topt->status == T_SUCCESS || topt->status == T_READONLY)
			printf("%u", *((u_long *) (topt + 1)));
		else
			printf("status = %ld", topt->status);
	}
	printf("\n");
}

#ifdef	notdef
void
xti_set_ulong_opt(int fd, const char *str, u_long level, u_long name)
{
	struct t_opthdr		*topt;

	topt = (struct t_opthdr *) req->opt.buf;
	topt->level = level;
	topt->name = name;
	topt->len = sizeof(struct t_opthdr);
	req->opt.len = topt->len;
	
	req->flags = T_CURRENT;
	printf("%s: ", str);
	if (t_optmgmt(fd, req, ret) == -1) {
		printf("t_optmgmt error\n");
	} else {
		topt = (struct t_opthdr *) ret->opt.buf;
		if (topt->status == T_SUCCESS || topt->status == T_READONLY)
			printf("%lu\n", *((u_long *) (topt + 1)));
		else
			printf("status = %ld\n", topt->status);
	}
}
#endif

int
main(int argc, char **argv)
{
	int					fd;

	if (argc != 2)
		err_quit("usage: checkopts <device>");

	fd = T_open(argv[1], O_RDWR, NULL);
	T_bind(fd, NULL, NULL);

	req = T_alloc(fd, T_OPTMGMT, T_ALL);
	ret = T_alloc(fd, T_OPTMGMT, T_ALL);

	xti_set_uchar_opt(fd, "T_IP_TOS", T_INET_IP, T_IP_TOS,
									SET_TOS(T_ROUTINE, T_LDELAY));
	xti_set_uchar_opt(fd, "T_IP_TTL", T_INET_IP, T_IP_TTL, 23);

	/* xti_def_ulong_opt(fd, "TCP_MAXSEG", INET_TCP, TCP_MAXSEG); */
	/* xti_def_ulong_opt(fd, "TCP_NODELAY", INET_TCP, TCP_NODELAY); */

	exit(0);
}
