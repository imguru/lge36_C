#!/bin/bash

read -p "input number: "

# if 문에서 참인지 거짓인지 판단하는 구문을 작성하는 방법.
# test
# test를 사용하면 then을 반드시 다음 라인에 작성해야 합니다.

# REPLY == 0
if test $REPLY -eq 0 
then
	echo "number is zero"
fi

# 한줄에 작성하기 위해서는 ;을 사용하면 됩니다.
if test $REPLY -ne 0; then
	echo "number is not zero"
fi
