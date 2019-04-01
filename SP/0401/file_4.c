
#include <stdio.h>

int main() {
	char buf[100];
	int ret;

	// Sleep(ms) -> #include <Windows.h>
	sleep(1) // sec -> #include <unistd.h>

	// fread(버퍼 주소, 블록의 개수, 버퍼의 크기, FILE *)
	// while ((ret = fread(buf, 1, sizeof buf, stdin)) != 0) {
	while (ret = fread(buf, 1, sizeof buf, stdin)) {
		fwrite(buf, 1, ret, stdout);
	}

	return 0;
}

