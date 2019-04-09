#include <unistd.h>

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>

#include <stdio.h>

// bind: Address already in use
//  : 해당 포트가 TIME_WAIT 상태로 인해, 바인드 할 수 없을 때 발생하는
//    오류의 입니다.

// TIME_WAIT 역활은 연결이 종료된 이후에 발생한 패킷이 이후 연결에 영향을 주지 않도록
// 해준다.
// 하지만, 새로운 연결을 생성할 때, seq 번호에 대한 할당이 이전과 전혀 상관없이 할당되므로
// 상관없다.

int main() {
	int ssock = socket(PF_INET, SOCK_STREAM, 0);
	if (ssock == -1) {
		perror("socket()");
		return -1;
	}

	// 서버 소켓의 포트에 대해서, TIME_WAIT 상태에도 바인드
	// 할 수 있도록 해줍니다.
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

	int csock = accept(ssock, (struct sockaddr *)&caddr, &socklen);
	printf("csock: %d\n", csock);
	
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
	close(ssock);
}




























