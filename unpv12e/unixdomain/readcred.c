#include	"unp.h"
#include	<sys/param.h>
#include	<sys/ucred.h>

ssize_t
read_cred(int fd, void *ptr, size_t nbytes, struct fcred *fcredptr)
{
	struct msghdr	msg;
	struct iovec	iov[1];
	ssize_t			n;

	union {
	  struct cmsghdr	cm;
	  char				control[CMSG_SPACE(sizeof(struct fcred))];
	} control_un;
	struct cmsghdr	*cmptr;

	msg.msg_control = control_un.control;
	msg.msg_controllen = sizeof(control_un.control);

	msg.msg_name = NULL;
	msg.msg_namelen = 0;

	iov[0].iov_base = ptr;
	iov[0].iov_len = nbytes;
	msg.msg_iov = iov;
	msg.msg_iovlen = 1;

	if ( (n = recvmsg(fd, &msg, 0)) < 0)
		return(n);

/* *INDENT-OFF* */
	if (fcredptr) {
		if (msg.msg_controllen > sizeof(struct cmsghdr)) {
			cmptr = CMSG_FIRSTHDR(&msg);

			if (cmptr->cmsg_len != CMSG_LEN(sizeof(struct fcred)))
				err_quit("control length = %d", cmptr->cmsg_len);
			if (cmptr->cmsg_level != SOL_SOCKET)
				err_quit("control level != SOL_SOCKET");
			if (cmptr->cmsg_type != SCM_CREDS)
				err_quit("control type != SCM_CREDS");
			memcpy(fcredptr, CMSG_DATA(cmptr), sizeof(struct fcred));
		} else
			bzero(fcredptr, sizeof(struct fcred)); /* none returned */
	}
/* *INDENT-ON* */

	return(n);
}
