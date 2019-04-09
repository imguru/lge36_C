#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <netinet/in.h>

#include <stdio.h>

#if 0
int select(int nfds, fd_set *readfds, fd_set *writefds,
		fd_set *exceptfds, struct timeval *timeout);

void FD_CLR(int fd, fd_set *set);
int  FD_ISSET(int fd, fd_set *set);
void FD_SET(int fd, fd_set *set);
void FD_ZERO(fd_set *set);

#endif

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

	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(ssock, &fds);  // server socket 디스크립터를 등록

#if 0
	for (int fd = 0; fd < nfds + 1 ; ++i) {
	}
	1. select의 nfds 인자는 등록한 디스크립터의 개수가 아니라,
	최대 디스크립터 값 + 1 이다.
	2. select는 등록된 디스크립터 집합에서 이벤트가 발생하면, 해당 디스크립터 집합의 내용을 변경한다.
	  => select를 호출하기전에, 별도로 백업을 해야 한다.

	한계
	  1) fd_set 이라는 자료구조를 사용하기 때문에,
	     1024개 이상의 디스크립터는 감시할 수 없다.
	  2) 성능에 한계가 있다.
	     이벤트가 발생한 디스크립터를 찾기 위해서는, 반드시 전체
		 집합을 순회해야 한다.
	  => poll

#endif
	int nfds = ssock;
	int fd;
	int ret;
	char buf[512];
	while (1) {
		fd_set readfds = fds;
		select(nfds + 1, &readfds, NULL, NULL, NULL);

		// accept
		if (FD_ISSET(ssock, &readfds)) {
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
			FD_SET(csock, &fds);
			if (nfds < csock) {
				nfds = csock;
			}
			//-----------------
		}

		for (fd = 4; fd < nfds + 1; ++fd) {
			if (FD_ISSET(fd, &readfds)) {  // client read
				ret = read(fd, buf, sizeof buf);			
				if (ret <= 0) {
					printf("연결이 종료되었습니다...\n");
					FD_CLR(fd, &fds);
				}
				write(fd, buf, ret);
			}
		}
	}

	close(ssock);
	return 0;
}
