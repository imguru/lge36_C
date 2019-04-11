// $ gcc server4.c -o server -lwiringPi -lpthread /root/wiringPi/wiringPi/softServo.c
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

#include <wiringPi.h>

//---------- Servo
#include <softServo.h>

#define SERVO_GPIO 25

int servo_on = 0;
void *servo_thread(void *arg) {
	while (1) {
		if (servo_on) {
			softServoWrite(SERVO_GPIO, -250);
			delay(300);

			softServoWrite(SERVO_GPIO, 1250);
			delay(300);
		}
	}
}
//----------
//---------- STEP
int step_on = 0;
#define STEP1 27
#define STEP2 24
#define STEP3 28
#define STEP4 29

int pin[4] = { STEP1, STEP2, STEP3, STEP4 };
int seq[8][4] = {
	{ 1,0,0,1 },
	{ 1,0,0,0 },
	{ 1,1,0,0 },
	{ 0,1,0,0 },
	{ 0,1,1,0 },
	{ 0,0,1,0 },
	{ 0,0,1,1 },
	{ 0,0,0,1 }
};

void forward(int step) {
	int i, j, k;

	for (i = 0;	i < step; ++i) {
		for (j = 0; j < 8; ++j) {
			for (k = 0; k < 4; ++k) {
				digitalWrite(pin[k], seq[j][k]);
			}
			delayMicroseconds(800);  // 800us
		}
	}
}

void *step_thread(void *arg) {
	while (1) {
		if (step_on) {
			forward(1024);
		}
	}
}
//----------------------


//----- FND -------
int led[8] = { 11, 10, 13, 12, 14, 15, 16, 0 };
int num[10] = {
	0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6
};

int fnd_value = 0;
void showDigit(int select, int value) {
	int i;
	int n = num[value];

	if (value < 0 || value > 9) {
		printf("out of index: %d\n", value);
		return;
	}

	for (i = 1; i <= 3; ++i) {
		digitalWrite(i, select == i);
	}

	for (i = 0; i < 8; ++i) {
		digitalWrite(led[i], n & (1 << (7 - i))); // !!
	}
}

void showDigit3(int value) {
	int n;
	int i;
	int arr[3];

	memset(arr, 0, sizeof arr);
	i = 0;
	while (value > 0) {
		arr[i++] = value % 10;
		value /= 10;
	}

	for (i = 0 ; i < 100; ++i) {
		showDigit(1, arr[2]);
		delay(1);
		showDigit(2, arr[1]);
		delay(1);
		showDigit(3, arr[0]);
		delay(1);
	}
}

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *fnd_thread(void *arg) {
	while (1) {
		// pthread_mutex_lock(&mutex);
		showDigit3(fnd_value);
		// pthread_mutex_unlock(&mutex);
	}

	return 0;
}

//-----------------

#define SW1 4
#define SW2 5

int mode = 0;
void on_switch1(void) {
	printf("버튼 1\n");
	mode = 0;
}

void on_switch2(void) {
	printf("버튼 2\n");
	mode = 1;
}

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
	wiringPiSetup();

	pinMode(SW1, INPUT);
	pinMode(SW2, INPUT);

	wiringPiISR(SW1, INT_EDGE_FALLING, on_switch1);
	wiringPiISR(SW2, INT_EDGE_FALLING, on_switch2);
	
	//-------- FND ----------
	int i;
	for (i = 0; i < 8; ++i) {
		pinMode(led[i], OUTPUT);
	}

	for (i = 0; i < 3; ++i) {
		pinMode(i + 1, OUTPUT);
	}

	pthread_t thread;
	pthread_create(&thread, NULL, fnd_thread, NULL);
	pthread_detach(thread);
	//------------------------

	//---- Servo
	softServoSetup(SERVO_GPIO, -1, -1, -1, -1, -1, -1, -1);
	pthread_t servothread;
	pthread_create(&servothread, NULL, servo_thread, NULL);
	pthread_detach(servothread);
	//----

	//---- STEP
	for (i = 0; i < 4; ++i) {
		pinMode(pin[i], OUTPUT);
	}
	pthread_t stepthread;
	pthread_create(&stepthread, NULL, step_thread, NULL);
	pthread_detach(stepthread);
	//---

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

			servo_on = temp >= 33;
			step_on = cds >= 1024;

			// pthread_mutex_lock(&mutex);
			if (mode == 0) {
				fnd_value = temp;
			} else {
				fnd_value = cds;
			}
			// pthread_mutex_unlock(&mutex);

			printf("%d - temp: %d, cds: %d\n", ++i, temp, cds);
		}

		close(csock);
		printf("클라이언트와 연결이 종료되었습니다..\n");
	}

	close(ssock);
	return 0;
}

