#include <unistd.h>
#include <stdio.h>

// l: list
// v: vector
//  => 프로그램의 인자로 전달하는 방식
// p: path(PATH)
//        프로그램을 실행하였을 때, 프로그램이 존재를 탐색하는 경로

//   argv[0]  argv[1]
// $ ls        -l
//  int main(argc, argv)
int main() {

	printf("hello, world...\n");

	// execl("/bin/ls", "ls", "-a", "-l", (char*)0);  
	char *argv[] = {
		"ls", "-a", "-l", NULL,
	};

	// execv("/bin/ls", argv);

	// 쓸거면 아래걸 쓰도록...
	// execlp("ls", "ls", "-a", "-l", (char*)0);  
	// execvp("ls", argv);

	char *env[] = {
		"NAME=Tom", NULL,
	};
	execle("./a.out", "./a.out", NULL, env);

	printf("ok..good.\n");
}









