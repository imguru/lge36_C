# /bin/bash

# Ctrl+C: SIGINT
# 기본 동작은 프로그램의 종료 입니다.
# SIGKILL, SIGCONT, SIGSTOP는 변경이 불가능합니다.

foo() {
	echo "call foo() - Ctrl + C"
}

# trap "echo 'Ctrl + C'" SIGINT 
trap "foo" SIGINT

for ((i=1; i<=10; ++i)); do
	echo "Loop $i"
	sleep 1
done
