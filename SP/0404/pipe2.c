#include <unistd.h>
#include <stdio.h>

// fork() + pipe()
//  : 부모와 자식간의 데이터 교환
//  => 부모가 open 한 파일을 자식이 물려 받는다.
//  => 사용하지 않는 디스크립터는 반드시 닫아야 합니다.

// $ ls | sort
// $ ./a.out ls sort
int main(int argc, char* argv[]) {
	int fd[2];
	pid_t pid;

	pipe(fd);

	if ((pid = fork()) == 0) {
		close(fd[1]);  // 자식은 read 채널을 사용하기 때문에, write를 닫습니다.
		dup2(fd[0], 0);
		execlp(argv[2], argv[2], NULL);
		perror("execlp");
		exit(1);
	}

	close(fd[0]); // 부모는 write 채널을 사용하기 때문에, read를 닫아야 합니다.
	dup2(fd[1], 1);
	execlp(argv[1], argv[1], NULL);
}










