#include	"unpxti.h"

int
main(int argc, char **argv)
{
	int					fd;
	struct t_info		tinfo;
	struct t_call		*tcallptr;
	struct t_unitdata	*tudataptr;

	if (argc != 2)
		err_quit("usage: prtinfo <device>");

	fd = T_open(argv[1], O_RDWR, &tinfo);

	printf("Device = %s\n", argv[1]);
	printf("%8ld: max size of address\n", tinfo.addr);
	printf("%8ld: max #bytes of options\n", tinfo.options);
	printf("%8ld: max size of data unit\n", tinfo.tsdu);
	printf("%8ld: max size of expedited data unit\n", tinfo.etsdu);
	printf("%8ld: max amount of data with connect\n", tinfo.connect);
	printf("%8ld: max amount of data with disconnect\n", tinfo.discon);
	printf("%8ld: service type\n", tinfo.servtype);
	printf("%8lx: flags\n", tinfo.flags);

	if (tinfo.servtype == T_CLTS) {
		tudataptr = T_alloc(fd, T_UNITDATA, T_ALL);
		printf("addr = %d, opt = %d, udata = %d\n",
				tudataptr->addr.maxlen, tudataptr->opt.maxlen,
				tudataptr->udata.maxlen);
		T_free(tudataptr, T_UNITDATA);
#ifdef	notdef
		if ( (tudataptr = t_alloc(fd, T_UNITDATA, T_UDATA)) != NULL)
			err_quit("expected error from t_alloc");
		if (t_errno != TSYSERR || errno != EINVAL)
			err_quit("t_errno = %d, errno = %d", t_errno, errno);
#endif
	} else {
		tcallptr = T_alloc(fd, T_CALL, T_ALL);
		printf("addr = %d, opt = %d, udata = %d\n",
				tcallptr->addr.maxlen, tcallptr->opt.maxlen,
				tcallptr->udata.maxlen);
		T_free(tcallptr, T_CALL);
		if (tcallptr->udata.maxlen == 0) {
			if ( (tcallptr = t_alloc(fd, T_CALL, T_UDATA)) != NULL)
				err_quit("expected error from t_alloc");
			if (t_errno != TSYSERR || errno != EINVAL)
				err_quit("t_errno = %d, errno = %d", t_errno, errno);
		}
	}

	exit(0);
}
