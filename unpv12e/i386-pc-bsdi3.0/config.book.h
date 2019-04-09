/* *INDENT-OFF* */
/* config.h.  Generated automatically by configure.  */
/* Define the following if you have the corresponding header */
#define	CPU_VENDOR_OS "i386-pc-bsdi3.0"
/* #undef	HAVE_NETCONFIG_H */		/* <netconfig.h> */
/* #undef	HAVE_NETDIR_H */		/* <netdir.h> */
#define	HAVE_PTHREAD_H 1			/* <pthread.h> */
#define	HAVE_STRINGS_H 1			/* <strings.h> */
/* #undef	HAVE_XTI_INET_H */		/* <xti_inet.h> */
#define	HAVE_SYS_FILIO_H 1			/* <sys/filio.h> */
#define	HAVE_SYS_IOCTL_H 1			/* <sys/ioctl.h> */
#define	HAVE_SYS_SELECT_H 1			/* <sys/select.h> */
#define	HAVE_SYS_SOCKIO_H 1			/* <sys/sockio.h> */
#define	HAVE_SYS_SYSCTL_H 1			/* <sys/sysctl.h> */
#define	HAVE_SYS_TIME_H 1			/* <sys/time.h> */

/* Define if we can include <time.h> with <sys/time.h> */
#define	TIME_WITH_SYS_TIME 1

/* Define the following if the function is provided */
#define	HAVE_BZERO 1
#define	HAVE_GETHOSTBYNAME2 1
/* #undef	HAVE_PSELECT */
#define	HAVE_VSNPRINTF 1

/* Define the following if the function prototype is in a header */
/* #undef	HAVE_GETADDRINFO_PROTO */		/* <netdb.h> */
/* #undef	HAVE_GETNAMEINFO_PROTO */		/* <netdb.h> */
#define	HAVE_GETHOSTNAME_PROTO 1			/* <unistd.h> */
#define	HAVE_GETRUSAGE_PROTO 1				/* <sys/resource.h> */
#define	HAVE_HSTRERROR_PROTO 1				/* <netdb.h> */
/* #undef	HAVE_IF_NAMETOINDEX_PROTO */	/* <net/if.h> */
#define	HAVE_INET_ATON_PROTO 1				/* <arpa/inet.h> */
#define	HAVE_INET_PTON_PROTO 1				/* <arpa/inet.h> */
/* #undef	HAVE_ISFDTYPE_PROTO */			/* <sys/stat.h> */
/* #undef	HAVE_PSELECT_PROTO */			/* <sys/select.h> */
#define	HAVE_SNPRINTF_PROTO 1				/* <stdio.h> */
/* #undef	HAVE_SOCKATMARK_PROTO */		/* <sys/socket.h> */

/* Define the following if the structure is defined. */
/* #undef	HAVE_ADDRINFO_STRUCT */			/* <netdb.h> */
/* #undef	HAVE_IF_NAMEINDEX_STRUCT */		/* <net/if.h> */
#define	HAVE_SOCKADDR_DL_STRUCT 1			/* <net/if_dl.h> */
#define	HAVE_TIMESPEC_STRUCT 1				/* <time.h> */

/* Define the following if feature is provided. */
#define	HAVE_SOCKADDR_SA_LEN 1		/* sockaddr{} has sa_len member */
#define	HAVE_MSGHDR_MSG_CONTROL 1	/* msghdr{} has msg_control member */
/* $$.Ic HAVE_SOCKADDR_SA_LEN$$ */
/* $$.Ic HAVE_MSGHDR_MSG_CONTROL$$ */

/* Names of XTI devices for TCP and UDP */
/* #undef	HAVE_DEV_TCP */					/* most XTI have devices here */
/* #undef	HAVE_DEV_XTI_TCP */				/* AIX has them here */
/* #undef	HAVE_DEV_STREAMS_XTISO_TCP */	/* OSF 3.2 has them here */

/* Define the following to the appropriate datatype, if necessary */
/* #undef	int8_t */					/* <sys/types.h> */
/* #undef	int16_t */					/* <sys/types.h> */
/* #undef	int32_t */					/* <sys/types.h> */
#define	uint8_t unsigned char			/* <sys/types.h> */
#define	uint16_t unsigned short			/* <sys/types.h> */
#define	uint32_t unsigned int			/* <sys/types.h> */
/* #undef	size_t */					/* <sys/types.h> */
/* #undef	ssize_t */					/* <sys/types.h> */
/* socklen_t should be typedef'd as uint32_t, but configure defines it
   to be an unsigned int, as it is needed early in the compile process,
   sometimes before some implementations define uint32_t. */
#define	socklen_t unsigned int			/* <sys/socket.h> */
#define	sa_family_t SA_FAMILY_T			/* <sys/socket.h> */
#define	SA_FAMILY_T uint8_t

#define	t_scalar_t int32_t				/* <xti.h> */
#define	t_uscalar_t uint32_t			/* <xti.h> */

/* Define the following, if system suports the feature */
#define	IPV4 1				/* IPv4, uppercase V name */
#define	IPv4 1				/* IPv4, lowercase v name, just in case */
/* #undef	IPV6 */			/* IPv6, uppercase V name */
/* #undef	IPv6 */			/* IPv6, lowercase v name, just in case */
#define	UNIXDOMAIN 1		/* Unix domain sockets */
#define	UNIXdomain 1		/* Unix domain sockets */
#define	MCAST 1				/* multicasting support */
/* *INDENT-ON* */
