#include	"unpxti.h"

int
xti_rdwr(int fd)
{
	return(ioctl(fd, I_PUSH, "tirdwr"));
}
