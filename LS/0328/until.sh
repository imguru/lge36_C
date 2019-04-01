#! /bin/bash

# i가 5보다 커질때까지 동작하고 싶다.
# until: 주어진 조건이 참이 될 때까지 루프 블록을 수행합니다.

i=1
until (( $i > 5 ))
do
	printf "%d: hello, world\n" $i
	let ++i
done
