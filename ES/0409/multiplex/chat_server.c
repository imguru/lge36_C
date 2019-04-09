#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdio.h>
#include <string.h>

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

	int efd = epoll_create1(0);
	if (efd == -1) {
		perror("epoll_create1");
		return 1;
	}

	struct epoll_event event = {0, };
	event.events = EPOLLIN;
	event.data.fd = ssock;

	epoll_ctl(efd, EPOLL_CTL_ADD, ssock, &event);

	int i;
	int j;
	int ret;
	char buf[512];
	int compress = 0;

	struct epoll_event revents[1024];
	int clients[1024];
	int nclients = 0;

	int n;

	while (1) {
		n = epoll_wait(efd, revents, 1024, -1);

		for (i = 0; i < n; ++i) {
			if (revents[i].events & EPOLLIN) {
				if (revents[i].data.fd == ssock) {  // accept
					struct sockaddr_in caddr = {0, };
					socklen_t caddrlen = sizeof caddr;
					int csock = accept(ssock, (struct sockaddr *)&caddr, &caddrlen);
					if (csock == -1) {
						perror("accept");
						return 1;
					}

					printf("client: %s %d\n", inet_ntoa(caddr.sin_addr), 
							ntohs(caddr.sin_port));

					event.data.fd = csock;
					event.events = EPOLLIN;
					epoll_ctl(efd, EPOLL_CTL_ADD, csock, &event);
					
					clients[nclients++] = csock;

				} else {                   // read
					int fd = revents[i].data.fd;
					ret = read(fd, buf, sizeof buf);			
					if (ret <= 0) {
						printf("연결이 종료되었습니다...\n");
						close(fd);

						epoll_ctl(efd, EPOLL_CTL_DEL, fd, NULL);
						for (j = 0; j < nclients; ++j) {
							if (clients[j] == fd) {
								clients[j] = clients[nclients - 1];
								nclients--;
								break;
							}
						}
					}

					for (j = 0; j < nclients; ++j) {
						write(clients[j], buf, ret);
					}
				}
			}
		}
	}

	close(ssock);
	return 0;
}







