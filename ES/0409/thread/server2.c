#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdio.h>
#include <pthread.h>

// Thread per connection server
//  : 새로운 클라이언트마다 데이터를 교환하기 위한 스레드를 생성한다.
void *thread_handler(void *arg) {
	int csock = (intptr_t)arg;  // !!
	int ret;
	char buf[64];
	while ((ret = read(csock, buf, sizeof buf)) > 0) {
		write(csock, buf, ret);
	}

	close(csock);
	printf("클라이언트와 연결이 종료되었습니다..\n");

	return 0;
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

		pthread_t thread;
		intptr_t arg = csock;
		pthread_create(&thread, NULL, thread_handler, (void *)arg);
		pthread_detach(thread);
		// pthread_join을 비동기적으로 호출하는 것이 어렵다.
		// pthread_detach를 사용하면, 스레드가 종료할 경우, 스스로의 자원을
		// 파괴한다.
		//  = signal(SIGCHLD, SIG_IGN);

		// pthread_join(thread, NULL);
	}

	close(ssock);
	return 0;
}







