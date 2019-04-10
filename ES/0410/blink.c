#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void led_control(int gpio) {
	int fd;
	char buf[32];

	// echo $gpio > /sys/class/gpio/export
	fd = open("/sys/class/gpio/export", O_WRONLY);
	sprintf(buf, "%d", gpio);
	write(fd, buf, strlen(buf));
	close(fd);

	// echo out > /sys/class/gpio/gpio$gpio/direction
	sprintf(buf, "/sys/class/gpio/gpio%d/direction", gpio);
	fd = open(buf, O_WRONLY);
	write(fd, "out", 4);
	close(fd);

	// echo 1 > /sys/class/gpio/gpio$gpio/value
	sprintf(buf, "/sys/class/gpio/gpio%d/value", gpio);
	fd = open(buf, O_WRONLY);
	write(fd, "1", 2);
	close(fd);

	getchar();

	fd = open("/sys/class/gpio/unexport", O_WRONLY);
	sprintf(buf, "%d", gpio);
	write(fd, buf, strlen(buf));
	close(fd);
}

int main(int argc, char **argv) {
	int gno;

	if (argc < 2) {
		fprintf(stderr, "Usage: ./a.out GPIO_NO\n");
		return -1;
	}

	gno = atoi(argv[1]);
	led_control(gno);

	return 0;
}























