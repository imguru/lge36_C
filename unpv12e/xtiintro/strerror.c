#include	"unpxti.h"

int
main(int argc, char **argv)
{
	printf("%s\n", t_strerror(TPROTO));

	errno = ETIMEDOUT;
	printf("%s\n", t_strerror(TSYSERR));

	t_errno = TSYSERR;
	errno = ETIMEDOUT;
	t_error("t_error says");

	t_errno = TSYSERR;
	errno = ETIMEDOUT;
	err_xti("err_xti says");

	exit(0);
}
