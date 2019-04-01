#! /bin/bash

clear
echo " 메뉴 선택
1. 메뉴1
2. 메뉴2
0. 종료"

read -p "입력[0-3]: "
case $REPLY in
	0) echo "종료 선택"
	  exit;;
	1) echo "메뉴1 선택"
	  exit;;
	2) echo "메뉴2 선택"
	  exit;;
	*) echo "잘못된 입력 입니다." >&2
	  exit;;
esac
