/* include if_indextoname */
#include	"unpifi.h"
#include	"unproute.h"

char *
if_indextoname(unsigned int index, char *name)
{
	char				*buf, *next, *lim;
	size_t				len;
	struct if_msghdr	*ifm;
	struct sockaddr		*sa, *rti_info[RTAX_MAX];
	struct sockaddr_dl	*sdl;

	if ( (buf = net_rt_iflist(0, index, &len)) == NULL)
		return(NULL);

	lim = buf + len;
	for (next = buf; next < lim; next += ifm->ifm_msglen) {
		ifm = (struct if_msghdr *) next;
		if (ifm->ifm_type == RTM_IFINFO) {
			sa = (struct sockaddr *) (ifm + 1);
			get_rtaddrs(ifm->ifm_addrs, sa, rti_info);
			if ( (sa = rti_info[RTAX_IFP]) != NULL) {
				if (sa->sa_family == AF_LINK) {
					sdl = (struct sockaddr_dl *) sa;
					if (sdl->sdl_index == index) {
						strncpy(name, sdl->sdl_data, sdl->sdl_nlen);
						name[sdl->sdl_nlen] = 0;	/* null terminate */
						free(buf);
						return(name);
					}
				}
			}

		}
	}
	free(buf);
	return(NULL);		/* no match for index */
}
/* end if_indextoname */

char *
If_indextoname(unsigned int index, char *name)
{
	char	*ptr;

	if ( (ptr = if_indextoname(index, name)) == NULL)
		err_quit("if_indextoname error for %d", index);
	return(ptr);
}
