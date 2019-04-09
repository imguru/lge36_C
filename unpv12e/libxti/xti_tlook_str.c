#include	"unpxti.h"

char *
xti_tlook_str(int fd)
{
	int	event;

	if ( (event = t_look(fd)) < 0)
		return(NULL);

	if (event == T_LISTEN)			return("T_LISTEN");
	else if (event == T_CONNECT)	return("T_CONNECT");
	else if (event == T_DATA)		return("T_DATA");
	else if (event == T_EXDATA)		return("T_EXDATA");
	else if (event == T_DISCONNECT)	return("T_DISCONNECT");
	else if (event == T_UDERR)		return("T_UDERR");
	else if (event == T_ORDREL)		return("T_ORDREL");
	else if (event == T_GODATA)		return("T_GODATA");
	else if (event == T_GOEXDATA)	return("T_GOEXDATA");
	else if (event == 0)			return("no event exists");
	return("unknown event");
}

char *
Xti_tlook_str(int fd)
{
	char	*str;

	if ( (str = xti_tlook_str(fd)) == NULL)
		err_xti("xti_tlook_str error");
	return(str);
}
