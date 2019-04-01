#! /bin/bash

arr=(1024 42 "one" $(pwd))

# 배열의 이름은 배열의 첫번째 원소를 참조한다.
echo $arr  # 1024
echo ${arr[0]}
echo ${arr[1]}

arr2=([10]="ten" [0]="one" [33]="two") # Map
echo ${arr2[10]}
echo ${arr2[0]}
echo ${arr2[33]}
echo ${arr2[1]}

arr3[0]="zero1"
arr3[1]="one1"

for i in 0 1; do
	echo ${arr3[$i]}
done



