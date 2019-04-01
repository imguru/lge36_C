#! /bin/bash
# unset: 변수의 값을 삭제하는 목적으로 사용된다.

a=42
echo $a
unset a
echo $a

arr=(0 1 2 3 4 5 6 7 8 9 10 [33]=33)
echo ${arr[33]}
echo ${arr[*]}

unset arr[2]
echo ${arr[*]}

unset arr
echo ${arr[*]}
