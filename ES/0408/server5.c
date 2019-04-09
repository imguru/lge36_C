#include <unistd.h>

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>

// Process per connection
// - 부모 프로세스는 accept을 계속 수행한다.
// - 자식 프로세스는 클라이언트와 데이터를 교환하는 목적으로
//   사용한다.
// fork()

#include <signal.h>
#include <sys/wait.h>

// 주의사항
// 1) 각 프로세스가 사용하지 않는 파일 디스크립터는 반드시 닫아야 한다.
//    커널 내부의 struct file에 대한 파괴 시점은 참조가 더 이상 존재하지
//    않을 때 수행된다.
// 2) 클라이언트(자식 프로세스)의 종료 시점은 알 수 없다.
//   => 비동기적인 형태로 처리해야 한다.

#if 0
void on_disconnect(int signo) {
	while (waitpid(-1, NULL, WNOHANG) > 0) {
		printf("연결이 종료되었습니다...\n");
	}
}
#endif

int main() {
	signal(SIGCHLD, SIG_IGN);
	// 좀비 프로세스를 wait을 호출하지 않고도 처리하는 방법.

	int ssock = socket(PF_INET, SOCK_STREAM, 0);
	if (ssock == -1) {
		perror("socket()");
		return -1;
	}

	int option = 1;
	setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof option);

	struct sockaddr_in saddr = {0, };
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = INADDR_ANY;
	saddr.sin_port = htons(5000);
	if (bind(ssock, (struct sockaddr *)&saddr, sizeof saddr) == -1) {
		perror("bind");
		return -1;
	}

	listen(ssock, SOMAXCONN);
	struct sockaddr_in caddr = {0, };
	socklen_t socklen = sizeof caddr;

	while (1) {
		int csock = accept(ssock, (struct sockaddr *)&caddr, &socklen);
		printf("csock: %d\n", csock);

		pid_t pid = fork();
		if (pid == 0) {
			close(ssock);

			char buf[128];
			while (1) {
				int ret = read(csock, buf, sizeof buf);
				if (ret == 0) {
					printf("연결이 종료되었습니다.\n");
					break;
				} else if (ret == -1) {
					perror("read");
					break;
				} else {
					write(csock, buf, ret);
				}
			}
			close(csock);
			exit(0);
		} else if (pid == -1) {
			perror("fork");
			exit(1);
		}

		close(csock);
	}

	close(ssock);
}




























