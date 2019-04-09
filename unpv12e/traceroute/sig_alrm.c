#include	"trace.h"

void
sig_alrm(int signo)
{
	return;		/* just interrupt the recvfrom() */
}
