#include	"unpifi.h"
#include	"ntp.h"

#define	MAXNADDRS	128			/* max # of addresses to bind() */
typedef struct {
  struct sockaddr *addr_sa;		/* ptr to bound address */
  socklen_t		   addr_salen;	/* socket address length */
  const char	  *addr_ifname;	/* interface name, for multicasting */
  int			   addr_fd;		/* socket descriptor */
  int			   addr_flags;	/* ADDR_xxx flags (see below) */
} Addrs;

Addrs	addrs[MAXNADDRS];		/* the actual array of structs */
int		naddrs;					/* index into the array */

#define	ADDR_BCAST	1
#define	ADDR_MCAST	2

const int	on;					/* for setsockopt() */

				/* function prototypes */
void	bind_mcast(const char *, SA *, socklen_t, int);
void	bind_ubcast(SA *, socklen_t, int, int, int);
void	read_loop(void);
void	sntp_proc(char *, ssize_t nread, struct timeval *);
void	sntp_send(void);
