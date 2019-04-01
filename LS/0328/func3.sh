#! /bin/bash
# 매개 변수의 값을 수정할 수 없고, 읽기만 가능하다.

foo() {
	echo $0  # 스크립트의 이름 
	echo $1
	echo $2
	echo $3

	# 인자를 10개 이상 전달할 경우, 중괄호로 감싸 주어야 한다.
	echo ${10}

	echo $#
}

foo 10 20 30 40 5 6 7 8 9 10

echo $0  # 스크립트의 이름 
echo $1
echo $2
echo $3

# 전달된 인자의 개수
echo $#
