#!/bin/bash
# {}

# 문자열 길이 구하기
# ${#변수}

str="hello"
echo ${#str}

# substr
# expr substr "hello" 1 2
# 인덱스가 0부터 취급됩니다.
echo ${str:0:2}  # ${변수:시작index:길이}
echo ${str:1}    

# 부분 문자열을 삭제하는 기능도 제공됩니다.
str="ABCDEFABCDEF123"
# echo ${str#pattern}
# str="ABCDEFABCDEF123"
#      |----|
echo ${str#A*F}

# str="ABCDEFABCDEF123"
#      |----------|
echo ${str##A*F}

str="123ABCDEFABCDEF"
# str="123ABCDEFABCDEF"
#               |----|
echo ${str%A*F}

# str="123ABCDEFABCDEF"
#         |----------|
echo ${str%%A*F}

str="hellohello"
echo ${str/llo/???}
echo ${str//llo/???}

str="hellohello"
echo ${str/llo/???}   
echo ${str/%llo/???}
