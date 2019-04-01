#! /bin/bash

foo() {
	str="hello"
	echo "call foo"
	return    
}

goo() {
	local str2="hello"
	echo "call goo"
	return    
}

echo $str
foo
echo $str

echo $str2
goo
echo $str2


