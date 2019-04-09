#include <sys/types.h>       
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h> 
#include <signal.h> 
#include <sys/wait.h> 
#include <poll.h> 
#include "socklib.h"

#define CLI_MAX   100
int cli_info[CLI_MAX];
int cli_count=0;

int main()
{
	int i,j;
	char buff[1024];
    int sd, new_sd;
	int ret;
	int option = 1;
	struct sockaddr_in addr;
	struct sockaddr_in cli_addr; 
	socklen_t addrlen;
	struct pollfd fds[CLI_MAX];
	sd = Socket( AF_INET, SOCK_STREAM , 0 );
	memset( &addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(7777);
	addr.sin_addr.s_addr   = inet_addr("192.168.137.100");
	setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof option);

	Bind(sd, (struct sockaddr*)&addr, sizeof(addr));
	Listen(sd, 20);

	fds[0].fd = sd;
	fds[0].events = POLLIN;
	while(1)
	{
		for(i=0; i<cli_count; i++)
		{
			fds[i+1].fd = cli_info[i];
			fds[i+1].events = POLLIN;
		}
		poll( fds, cli_count+1, -1);
		if( fds[0].revents & POLLIN )
		{
			addrlen = sizeof( cli_addr );
			new_sd = Accept(sd, (struct sockaddr*)&cli_addr, &addrlen);
			cli_info[cli_count++] = new_sd;
			printf("client ip=%s, port=%d, 현재 접속자 수 : %d명\n", 
					inet_ntoa(cli_addr.sin_addr),
					ntohs(cli_addr.sin_port), cli_count);
		}
		for(i=0; i<cli_count; i++)
		{
			if( fds[i+1].revents & POLLIN )
			{
				ret = Read( cli_info[i], buff, sizeof buff );
				if( ret == 0 )
				{
					Close(cli_info[i]);
					--cli_count;
					if( i != cli_count )
						cli_info[i] = cli_info[cli_count];

					printf("연결이 정상 종료 되었습니다., 현재 접속자 수 : %d\n",
							cli_count);
					break;
				}
				Write( 1, buff, ret );
				for(j=0; j<cli_count; j++ )
					Write( cli_info[j], buff, ret );
			}
		}
	}
	Close(sd);
	return 0;
}

