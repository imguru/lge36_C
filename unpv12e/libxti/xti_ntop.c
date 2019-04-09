#include	"unpxti.h"

#ifdef	HAVE_SOCKADDR_DL_STRUCT
# include	<net/if_dl.h>
#endif

char *
xti_ntop(const struct netbuf *np)
{
    char			*name, portstr[7];
    static char 	str[128];	/* Unix domain is largest */
	struct sockaddr	*sa;

	name = str;     			/* use our static buffer */

	if (np->len == 0)
		return(NULL);
	sa = (struct sockaddr *) np->buf;

	switch (sa->sa_family) {
	case AF_INET: {
		struct sockaddr_in	*sin = (struct sockaddr_in *) sa;

		if (np->len != sizeof(struct sockaddr_in))
			goto loop;
		if (inet_ntop(AF_INET, &sin->sin_addr, name, sizeof(str)) == NULL)
			return(NULL);
		if (ntohs(sin->sin_port) != 0) {
			snprintf(portstr, sizeof(portstr), ".%d", ntohs(sin->sin_port));
			strcat(name, portstr);
		}
		return(name);
	}

#ifdef	IPV6
	case AF_INET6: {
		struct sockaddr_in6	*sin6 = (struct sockaddr_in6 *) sa;

		if (np->len != sizeof(struct sockaddr_in6))
			goto loop;

		if (inet_ntop(AF_INET6, &sin6->sin6_addr, name, sizeof(str)) == NULL)
			return(NULL);
		if (ntohs(sin6->sin6_port) != 0) {
			snprintf(portstr, sizeof(portstr), ".%d", ntohs(sin6->sin6_port));
			strcat(name, portstr);
		}
		return(name);
	}
#endif

#ifdef	AF_UNIX
	case AF_UNIX: {
		struct sockaddr_un	*unp = (struct sockaddr_un *) sa;

			/* OK to have no pathname bound to the socket: happens on
			   every connect() unless client calls bind() first. */
		if (unp->sun_path[0] == 0)
			strcpy(name, "(no pathname bound)");
		else
			sprintf(name, "%s", unp->sun_path);
		return(name);
	}
#endif

#ifdef	HAVE_SOCKADDR_DL_STRUCT
	case AF_LINK: {
		struct sockaddr_dl	*sdl = (struct sockaddr_dl *) sa;

		if (sdl->sdl_nlen > 0)
			sprintf(name, "%*s", sdl->sdl_nlen, &sdl->sdl_data[0]);
		else
			sprintf(name, "AF_LINK, index=%d", sdl->sdl_index);
		return(name);
	}
#endif

	/*
	 * XTI loopback addresses (/dev/clts, /dev/cots, /dev/cotsord) are
	 * "flex addresses", arbitrary sequences of octets.  These will not
	 * be in socket address structures.  They need not be null terminated.
	 * But, no conversion is required for this type of address (they are
	 * typically `hostname.servicename'.
	 * We assume this type of address if none of the above matched, and
	 * if there are no null bytes and no DEL bytes in the string.
	 */

	default: {
		u_int	i;
		u_char	*ptr;

loop:
		for (ptr = (u_char *) np->buf, i = 0; i < np->len; ptr++, i++)
			if (*ptr == 0 || *ptr == 0xff)
				return(NULL);

		/*
		 * We don't copy the sequence, as there is no limit on its length.
		 * So we just return a pointer to the sequence in the netbuf{}.
		 * Only problem is that it may not be null terminated.  Sigh.
		 * Didn't anyone think when they invented these addresses?
		 */

		return(np->buf);
	}
	}
}
