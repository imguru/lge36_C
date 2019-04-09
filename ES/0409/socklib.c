#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "socklib.h"
void err_sys(char *msg)
{
	perror(msg);
	exit(-1);
}
int Socket(int domain, int type, int protocol)
{
	int sd;
	sd = socket( domain, type , protocol );
	if( sd < 0  )
		err_sys("socket");
	return sd;
}
int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
	int ret;
	ret = bind( sockfd, addr, addrlen);
	if( ret < 0  )
		err_sys("bind");
	return ret;
}
int Listen(int sockfd, int backlog)
{
	int ret;
	ret = listen( sockfd, backlog );
	if( ret < 0  )
		err_sys("listen");
	return ret;
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
	int new_sd;
	new_sd = accept(sockfd, addr, addrlen);
	if( new_sd < 0  )
		err_sys("accept");
	return new_sd;
}

ssize_t Read(int fd, void *buf, size_t count)
{
	ssize_t ret;
	ret = read(fd,buf,count);
	if( ret < 0  )
		err_sys("read");
	return ret;
}

ssize_t Write(int fd, const void *buf, size_t count)
{
	ssize_t ret;
	ret = write(fd,buf,count);
	if( ret < 0  )
		err_sys("write");
	return ret;
}
int Close(int fd)
{
	int ret;
	ret = close(fd);
	if( ret < 0  )
		err_sys("close");
	return ret;
}

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
	int ret;
	ret = connect(sockfd, addr, addrlen);
	if( ret < 0  )
		err_sys("connect");
	return ret;
}












