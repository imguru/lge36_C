#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdio.h>
#include <errno.h>

struct packet {
	char *base;
	char *ptr;
	char *rptr;
};

void init_packet(struct packet *packet, char *buf) {
	packet->base = buf;
	packet->rptr = buf;

	packet->ptr = buf + sizeof(short);
}

int get_int32(struct packet *packet) {
	int ret = *(int *)packet->rptr;
	packet->rptr += sizeof(int);
	return ntohl(ret);
}

short get_int16(struct packet *packet) {
	short ret = *(short *)packet->rptr;
	packet->rptr += sizeof(short);
	return ntohs(ret);
}

// 패킷이 잘려서 오든, 빠르게 오든 일관적으로 처리할 수 있어야 한다.
//  => readn
ssize_t readn(int fd, void *vptr, size_t n)
{
	size_t  nleft;
	ssize_t nread;
	char    *ptr;

	ptr = vptr;
	nleft = n;
	while (nleft > 0) {
		if ( (nread = read(fd, ptr, nleft)) < 0) {
			if (errno == EINTR)
				nread = 0;  
			else
				return(-1);
		} else if (nread == 0)
			break;         

		nleft -= nread;
		ptr   += nread;
	}
	return(n - nleft);      /* return >= 0 */
}

int main() {
	int ssock = socket(PF_INET, SOCK_STREAM, 0);
	if (ssock == -1) {
		perror("socket");
		return 1;
	}

	int option = 1;
	setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof option);

	struct sockaddr_in saddr = {0, };
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = INADDR_ANY;
	saddr.sin_port = htons(5000);
	if (bind(ssock, (struct sockaddr *)&saddr, sizeof saddr) == -1) {
		perror("bind");
		return 1;
	}

	if (listen(ssock, SOMAXCONN) == -1) {
		perror("listen");
		return 1;
	}

	while (1) {
		struct sockaddr_in caddr = {0, };
		socklen_t caddrlen = sizeof caddr;
		int csock = accept(ssock, (struct sockaddr *)&caddr, &caddrlen);
		if (csock == -1) {
			perror("accept");
			return 1;
		}

		printf("client: %s\n", inet_ntoa(caddr.sin_addr));

		int ret;
		char buf[8];
		int i = 0;
		struct packet packet;
		while (1) {
			char *p;
			// 1. 패킷의 길이를 먼저 받아야 한다.
			short len;
			ret = readn(csock, buf, sizeof len);
			if (ret <= 0)
				break;

			len = ntohs(*(short *)buf);
			// 2. 패킷의 길이만큼만 read를 수행합니다.
			ret = readn(csock, buf, len);
			if (ret <= 0) {
				break;
			}
			
			init_packet(&packet, buf);
			int temp = get_int32(&packet);
			int cds = get_int32(&packet);

			printf("%d - temp: %d, cds: %d\n", ++i, temp, cds);
		}

		close(csock);
		printf("클라이언트와 연결이 종료되었습니다..\n");
	}

	close(ssock);
	return 0;
}

