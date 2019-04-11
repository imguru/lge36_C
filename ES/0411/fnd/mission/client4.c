#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>

#include <wiringPi.h>
#include <mcp3422.h>   // ADC!!

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

	wiringPiSetup();
	mcp3422Setup(400, 0x6a, 0, 0);

	printf("연결이 시작되었습니다...\n");
	char buf[64];
	int ret;

	int i, j;
	short len;
	struct packet packet;
	while (1) {
		int cds = analogRead(400);
		int temp = (analogRead(401) / 1000. - 0.5) * 100;

		init_packet(&packet, buf);
		put_int32(&packet, temp);
		put_int32(&packet, cds);

		len = build_packet(&packet);
		write(csock, packet.base, len);
	}
	
	close(csock);
	return 0;
}





