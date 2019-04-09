#include	"trace.h"

char *
icmpcode_v6(int code)
{
	switch (code) {
	case  ICMP6_DST_UNREACH_NOROUTE:
		return("no route to host");
	case  ICMP6_DST_UNREACH_ADMIN:
		return("administratively prohibited");
	case  ICMP6_DST_UNREACH_NOTNEIGHBOR:
		return("not a neighbor");
	case  ICMP6_DST_UNREACH_ADDR:
		return("address unreachable");
	case  ICMP6_DST_UNREACH_NOPORT:
		return("port unreachable");
	default:
		return("[unknown code]");
	}
}
