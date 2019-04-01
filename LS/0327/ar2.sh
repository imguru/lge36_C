#! /bin/bash
num=0
((num=num + 1))
echo $num

((num+=1))
((++num))
echo $num

((num = 2 ** 10))
echo $num

((ret = 10 > 1))
echo $ret

# ((result=2*2))
result=$((2*2))
echo $result

n1=10
n2=20
# ((result=$n1 + $n2))
((result=n1 + n2))
echo $result






