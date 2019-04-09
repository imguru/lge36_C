#include	"unpxti.h"

int
main(int argc, char **argv)
{
	int			fd;
	socklen_t	optlen;
	t_uscalar_t	mss, sendbuff;

	fd = T_open(XTI_TCP, O_RDWR, NULL);
	T_bind(fd, NULL, NULL);

	optlen = sizeof(mss);
	Xti_getopt(fd, T_INET_TCP, T_TCP_MAXSEG, &mss, &optlen);
	printf("TCP mss = %d\n", mss);

	sendbuff = 65536;
	Xti_setopt(fd, XTI_GENERIC, XTI_SNDBUF, &sendbuff, sizeof(sendbuff));

	optlen = sizeof(sendbuff);
	Xti_getopt(fd, XTI_GENERIC, XTI_SNDBUF, &sendbuff, &optlen);
	printf("send buffer size = %d\n", sendbuff);

	exit(0);
}
