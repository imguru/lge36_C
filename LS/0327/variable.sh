#! /bin/sh

name=Tom

echo name      # name
echo $name     # Tom
echo ${name}   # Tom
echo "$name"   # Tom
echo '$name'   # $name
echo "'$name'" # 'Tom'
echo \$name    # $name

# 명령어의 결과를 변수에 저장하는 것도 가능합니다.
# $(shell command) 또는 `shell command`
result=$(date)
echo $result

result=`ls -l`
echo "$result"


