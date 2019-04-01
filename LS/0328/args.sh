#! /bin/bash

# $* 변수를 사용하면 전체 인자 목록을 뽑아 올 수 있습니다.
echo \$*: $*
echo \$@: $@

# $*과 $@는 "" 함께 사용할 경우 차이가 있습니다.

# "10 20 30"
for i in "$*"; do
	echo $i
done

# "10" "20" "30"
for i in "$@"; do
	echo $i
done

foo() {
	for i in $*; do
		echo $i
	done
}

foo 100 200 300



