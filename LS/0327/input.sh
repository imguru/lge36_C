#! /bin/bash
# read 명령어를 통해, 표준 입력(키보드)으로 처리할 수 있다.
# read word1 word2 word3
# echo $word1
# echo $word2
# echo $word3

# 변수를 지정하지 않는 경우 REPLY라는 변수를 통해 처리할 수 있다.
# - bash
# read
# echo $REPLY

# prompt
read -p "name: "
echo $REPLY

read -p "age: " age
echo $age

# -s: 키보드 입력에 대한 echo를 비활성화한다.
read -p "password: " -s password
echo $password
