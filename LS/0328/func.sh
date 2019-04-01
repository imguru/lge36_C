#! /bin/bash

# bash
function foo {
	echo "call foo"
	return 1
}

goo() {
	echo "call goo"
	return    # 0
}

foo 
echo $?
goo

