#!/bin/bash

# 매개 변수를 반복적으로 처리하기 위해 shift 명령을 제공한다.
# shift 명령을 이용하면, 전체 값들을 왼쪽으로 하나씩 옮길 수 있다.

foo() {
	echo "foo - $#"
	while [ -n "$1" ]; do
		echo -n "$1 "
		shift
	done
	echo
}

arr=(1 2 3 4 5 5 10 20 30 40)
n=42

foo ${arr[*]} $n
