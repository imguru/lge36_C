#! /bin/sh
# expr은 명령어이기 때문에, 공백으로 구분한다.
result=$(expr 2 + 2)
result=`expr 2 + 2`
echo $result

n1=10
n2=20

# * 는 와일드카드로 사용이 되므로, 추가적인 처리가 필요합니다.
result=$(expr $n1 "*" $n2)
result=$(expr $n1 \* $n2)
echo $result

expr 0 "|" 10 
expr 4 \| 10 

expr 0 "&" 10 
expr 4 \& 10 



