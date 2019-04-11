#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>

// Packet
// temp(4):cds(4)
// TCP는 데이터의 경계가 존재하지 않으므로, 데이터를 보내기 전에,
// 길이를 보내야 한다.
struct packet {
	char *base;
	char *ptr;
};

void init_packet(struct packet *packet, char *buf) {
	packet->base = buf;
	packet->ptr = buf + sizeof(short);
}

void put_int32(struct packet *packet, int value) {
	*(int *)packet->ptr = htonl(value);
	packet->ptr += sizeof(int);
}

void put_int16(struct packet *packet, short value) {
	*(short *)packet->ptr = htons(value);
	packet->ptr += sizeof(short);
}

int build_packet(struct packet *packet) {
	short ret = packet->ptr - packet->base;
	*(short *)packet->base = htons(ret);

	return ret + sizeof(short);
}

int main() {
	int csock = socket(PF_INET, SOCK_STREAM, 0);
	if (csock == -1) {
		perror("socket");
		return 1;
	}

	struct sockaddr_in saddr = {0, };
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	saddr.sin_port = htons(5000);

	if (connect(csock, (struct sockaddr *)&saddr, sizeof saddr) == -1) {
		perror("connect");
		return 1;
	}

	printf("연결이 시작되었습니다...\n");
	char buf[64];
	int ret;

	// buf
	//   len(2):temp(4):cds(4)
	int i, j;
	short len;
	struct packet packet;
	while (1) {
		int cds = 42;
		int temp = 100;

		init_packet(&packet, buf);
		put_int32(&packet, temp);
		put_int32(&packet, cds);

		len = build_packet(&packet);
		write(csock, packet.base, len);
	}
	
	close(csock);
	return 0;
}





