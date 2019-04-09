#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <poll.h>
#include "socklib.h"

int main()
{
	int sd;
	int ret;
	struct pollfd fds[2];
	char buff[1024];
	struct sockaddr_in addr;
	sd = Socket( AF_INET, SOCK_STREAM , 0 );
	memset( &addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(7777);
	addr.sin_addr.s_addr   = inet_addr("192.168.137.100");
	Connect(sd, (struct sockaddr*)&addr, sizeof(addr));
	fds[0].fd = 0;
	fds[0].events = POLLIN;
	fds[1].fd = sd;
	fds[1].events = POLLIN;
	while(1) 
	{
		poll( fds, 2, -1);
		if( fds[0].events & POLLIN )
		{
			ret = Read(0, buff, sizeof buff  );
			if( ret > 0 )
			{
				Write( sd, buff, ret);
			}
			else
			{
				break;
			}
		}
		if( fds[1].events & POLLIN )
		{
			ret = Read( sd, buff, sizeof buff );
			Write( 1, buff, ret );
		}
	}
	Close(sd);
	return 0;
}

