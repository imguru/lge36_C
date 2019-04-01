# /bin/bash 

foo() {
	echo "call foo()"
}

# EXIT는 프로그램이 종료되는 시점에 호출되는 핸들러를 의미합니다.
set -x
trap "foo" EXIT

for ((i=1; i<=100; ++i)); do
	echo "Loop $i"
	sleep 1
done
set +x

# 제거합니다.
# trap -- EXIT



