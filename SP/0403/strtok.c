#include <unistd.h>
#include <stdio.h>
#include <string.h>

// getcwd: 현재 작업 디렉토리를 얻어오는 시스템 콜
int main() {
	char buf[128];
	getcwd(buf, sizeof buf);
	printf("pwd: %s\n", buf);

	while (fgets(buf, sizeof buf, stdin)) {
		if (strlen(buf) > 0) {
			buf[strlen(buf) - 1] = '\0';
		}

		printf("input: %s\n", buf);
	}
}

#if 0
int main() {
	char command[] = "ls -laR";
	char *p;

	for (p = strtok(command, " "); p != NULL; p = strtok(NULL, " ")) {
		printf("%s\n", p);
	}
}
#endif
