#! /bin/bash
# 비교 연산자를 사용할 때, 리다이렉션과 충돌이 있으므로
# 별도 처리가 필요합니다.
let ret=2\>0
let ret=2"<"0
let ret=2'>='0
let "ret = 2 <= 0"
echo $ret
