#include	"unpxti.h"

char *
xti_flags_str(int flags)
{
	if ((flags & (T_EXPEDITED | T_MORE)) == (T_EXPEDITED | T_MORE))
		return("T_EXPEDITED and T_MORE");
	else if (flags & T_EXPEDITED)
		return("T_EXPEDITED");
	else if (flags & T_MORE)
		return("T_MORE");
	else if (flags == 0)
		return("0");
	return("(unknown)");
}

char *
Xti_flags_str(int flags)
{
	char	*str;

	if ( (str = xti_flags_str(flags)) == NULL)
		err_xti("xti_flags_str error");
	return(str);
}
