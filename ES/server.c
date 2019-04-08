// TCP/IP 
//   : Socket Programming

// 1. socket(): socket 파일 생성.
// 2. bind(): socket에 주소를 등록하는 작업.
// 3. listen(): listen 소켓으로 변경한다.
// 4. aceept(): 연결을 수락한다.

// Echo Server / Client
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>

#include <stdio.h>

int main() {
	// struct sockaddr_in saddr;

	// socket: open과 동일하게 파일 디스크립터를 반환한다.
	// PF_INET: Protocol Family Internet
	// SOCK_STREAM: TCP / SOCK_DGRAM: UDP
	int ssock = socket(PF_INET, SOCK_STREAM, 0);
	if (ssock == -1) {
		perror("socket()");
		return -1;
	}

	printf("socket: %d\n", ssock);

	// 2. 소켓에 주소를 지정한다. - bind()
	//    IP 주소(32) / PORT 주소(16)
	// memset(&saddr, 0, sizeof saddr);
	struct sockaddr_in saddr = {0, };
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = INADDR_ANY;
	saddr.sin_port = htons(5000);
	// Little -> Big
	//      htons
	//      htonl

    // Big -> Little
	//      ntohs
	//      ntohl
#if 0
	int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
#endif
	// sockaddr_ 계열 구조체를 사용할 때, 함수로 넘길 때 반드시
	// sockaddr *로 넘겨야 한다.
	bind(ssock, (struct sockaddr *)&saddr, sizeof saddr);

	listen(ssock, SOMAXCONN);

	// accept: listen에 의해서 대기하고 있는 클라이언트 중 하나에 대한
	//         세션을 형성한다.
	struct sockaddr_in caddr = {0, };
	socklen_t socklen = sizeof caddr;

	int csock = accept(ssock, (struct sockaddr *)&caddr, &socklen);
	printf("csock: %d\n", csock);

}



























