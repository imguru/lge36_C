#! /bin/bash

i=0
while (( $i < 10 ))
do
	printf "%d: hello, world\n" $i
	let ++i

	if (( i == 5 )); then
		echo "i == 5"
		# break
		continue
	fi
done

