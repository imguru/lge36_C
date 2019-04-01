#! /bin/bash
for i in `ls`; do
	echo "$i: ok"
done

for i in $(cat for3.sh); do
	echo "$i"
done
