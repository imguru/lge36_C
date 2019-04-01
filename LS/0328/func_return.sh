#! /bin/bash
# 함수에서 반환을 수행하는 방법
# echo

foo() {
	echo "foo result"
}

ret=$(foo)
ret=`foo`
echo $ret
