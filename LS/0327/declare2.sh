#! /bin/bash
declare -i age=0
echo $age

age=10         # 대입도 가능하다.
echo $age      # 10

age="daniel"   # unbound variable 오류로 스크립트가 종료된다.
echo $age
echo $age

