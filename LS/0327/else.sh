#!/bin/bash
read -p "input number: "

# [expression]
# => test는 []와 동일하게 해석된다.
# 주의할 점: [] 사이에 반드시 공백이 존재해야 한다.

if [ $REPLY -eq 0 ]
then
	echo "number is zero"
fi

# 한줄에 작성하기 위해서는 ;을 사용하면 됩니다.
if [ $REPLY -ne 0 ]; then
	echo "number is not zero"
fi
