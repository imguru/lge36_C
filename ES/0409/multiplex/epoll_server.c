#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdio.h>
#include <string.h>

// epoll: 2.6 커널에서 도입되었습니다.
//  => poll 사용상의 단점을 보완하고, 성능을 개선한다.

// 1) epoll 저장소를 통해서, 디스크립터 배열을 커널이 관리한다.
//    epoll_ctl 함수를 통해 디스크립터를 등록/해지/수정할 수 있다.

// 2) poll이 반환하면, 이벤트가 발생한 디스크립터를 찾기 위해, 전체 배열을
//    순회해야 한다.
//    epoll은 이벤트가 발생한 배열을 만들어준다.
//    => epoll의 반환 배열만 체크해서 처리하면 됩니다.

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

	// 1. 저장소를 생성해야 합니다.
	//  : epoll_create는 더이상 사용되지 않습니다.
	int efd = epoll_create1(0);
	if (efd == -1) {
		perror("epoll_create1");
		return 1;
	}

	//---------------------
	// 2. 저장소에 감시하고자하는 디스크립터를 등록한다.
	struct epoll_event event = {0, };
	event.events = EPOLLIN;
	event.data.fd = ssock;

	epoll_ctl(efd, EPOLL_CTL_ADD, ssock, &event);
	//---------------------

	int i;
	int ret;
	char buf[512];
	int compress = 0;

	struct epoll_event revents[1024];
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

					printf("client: %s\n", inet_ntoa(caddr.sin_addr));

					// 감시하고자 하는 디스크립터를 등록한다.
					//-----------------
					event.data.fd = csock;
					event.events = EPOLLIN;
					epoll_ctl(efd, EPOLL_CTL_ADD, csock, &event);
					//-----------------
				} else {                   // read
					int fd = revents[i].data.fd;
					ret = read(fd, buf, sizeof buf);			
					if (ret <= 0) {
						printf("연결이 종료되었습니다...\n");
						close(fd);

						// 연결이 종료된 디스크립터에 대한 감시를 종료한다.
						//--------------
						epoll_ctl(efd, EPOLL_CTL_DEL, fd, NULL);
						//--------------
					}
					write(fd, buf, ret);
				}
			}
		}
	}

	close(ssock);
	return 0;
}







