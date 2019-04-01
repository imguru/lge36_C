#! /bin/bash

i=1
while (( $i <= 5 ))
do
	printf "%d: hello, world\n" $i
	let ++i
done

i=1
while (( $i <= 5 )); do
	printf "%d: hello, world\n" $i
	let ++i
done

i=1
while true; do
	printf "%d: hello, world\n" $((i++))
done
