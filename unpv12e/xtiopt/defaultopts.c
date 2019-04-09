#include	"unpxti.h"

static	struct t_optmgmt	*req, *ret;

void
xti_def_uchar_opt(int fd, const char *str, t_scalar_t level, t_scalar_t name)
{
	struct t_opthdr		*topt;

	topt = (struct t_opthdr *) req->opt.buf;
	topt->level = level;
	topt->name = name;
	topt->len = sizeof(struct t_opthdr);
	req->opt.len = topt->len;
	
	req->flags = T_DEFAULT;
	printf("%s: ", str);
	if (t_optmgmt(fd, req, ret) == -1) {
		printf("t_optmgmt error\n");
	} else {
		topt = (struct t_opthdr *) ret->opt.buf;
		printf("len = %d, ", topt->len);
		if (topt->status == T_SUCCESS || topt->status == T_READONLY)
			printf("%u\n", *((u_char *) (topt + 1)));
		else
			printf("status = %ld\n", topt->status);
	}
}

void
xti_def_uscalar_opt(int fd, const char *str, t_uscalar_t level, t_uscalar_t name)
{
	struct t_opthdr		*topt;

	topt = (struct t_opthdr *) req->opt.buf;
	topt->level = level;
	topt->name = name;
	topt->len = sizeof(struct t_opthdr);
	req->opt.len = topt->len;
	
	req->flags = T_DEFAULT;
	printf("%s: ", str);
	if (t_optmgmt(fd, req, ret) == -1) {
		printf("t_optmgmt error\n");
	} else {
		topt = (struct t_opthdr *) ret->opt.buf;
		printf("len = %d, ", topt->len);
		if (topt->status == T_SUCCESS || topt->status == T_READONLY)
			printf("%u\n", *((t_uscalar_t *) (topt + 1)));
		else
			printf("status = %ld\n", topt->status);
	}
}

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

	xti_def_uchar_opt(fd, "T_IP_TOS", T_INET_IP, T_IP_TOS);
	xti_def_uchar_opt(fd, "T_IP_TTL", T_INET_IP, T_IP_TTL);

	xti_def_uscalar_opt(fd, "T_TCP_MAXSEG", T_INET_TCP, T_TCP_MAXSEG);
	xti_def_uscalar_opt(fd, "T_TCP_NODELAY", T_INET_TCP, T_TCP_NODELAY);

	exit(0);
}
