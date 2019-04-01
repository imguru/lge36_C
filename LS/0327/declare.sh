#! /bin/bash
# 변수의 기본 형태는 문자열이다.
declare -i a=10
declare -i b=20
declare -i result=0

# result=a+b
result="$a + $b"

# echo $a+$b # 주의해야 한다.
echo $result

#a=3.14   # Error!
# a=Tom     # 0으로 처리된다.
# echo $a

declare -i x

x=2#1010
echo $x

x=8#17
echo $x

x=16#ff
echo $x

x=3#22
echo $x










