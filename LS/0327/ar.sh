#! /bin/bash
result=$[2 * 2]
echo $result

result=$[2 ** 10]
echo $result

var1=10
var2=20

echo $[var1 > var2]   # 0
echo $[var1 < var2]   # 1
echo $[var1 >= var2]  # 0
echo $[var1 <= var2]  # 1
echo $[var1 == var2]  # 0,
echo $[var1 != var2]  # 1

