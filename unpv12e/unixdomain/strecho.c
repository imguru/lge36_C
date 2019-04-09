#include	"unp.h"
#include	<sys/param.h>
#include	<sys/ucred.h>

ssize_t	 read_cred(int, void *, size_t, struct fcred *);

void
str_echo(int sockfd)
{
	ssize_t			n;
	const int		on = 1;
	char			line[MAXLINE];
	struct fcred	cred;

	Setsockopt(sockfd, 0, LOCAL_CREDS, &on, sizeof(on));

	if ( (n = read_cred(sockfd, NULL, 0, &cred)) < 0)
		err_sys("read_cred error");
	if (cred.fc_ngroups == 0)
		printf("(no credentials returned)\n");
	else {
		printf("real user ID = %d\n", cred.fc_ruid);
		printf("real group ID = %d\n", cred.fc_rgid);
		printf("login name = %-*s\n", MAXLOGNAME, cred.fc_login);
		printf("effective user ID = %d\n", cred.fc_uid);
		printf("effective group ID = %d\n", cred.fc_gid);
		printf("%d supplementary groups:", cred.fc_ngroups - 1);
		for (n = 1; n < cred.fc_ngroups; n++)	/* [0] is the egid */
			printf(" %d", cred.fc_groups[n]);
		printf("\n");
	}

	for ( ; ; ) {
		if ( (n = Readline(sockfd, line, MAXLINE)) == 0)
			return;		/* connection closed by other end */

		Writen(sockfd, line, n);
	}
}
