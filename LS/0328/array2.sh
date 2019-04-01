#!/bin/bash
animals=("dog" "cat" "fish")

animals[100]="Tom"

echo ${animals[0]}
echo ${animals[1]}
echo ${animals[2]}

echo ${animals[*]}

# 배열의 개수를 출력하는 방법
echo ${#animals[@]}

# 배열의 요소를 순회하는 방법
for i in ${animals[*]}; do
	echo $i
done

