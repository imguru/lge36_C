#! /bin/bash

read -p "입력: "

# [[ ]]
case $REPLY in
	hello) echo "hello"
	  exit;;
	world) echo "world"
	  exit;;
	show|me|the|money) echo "show me the money"
	  exit;;
	??????) echo "6글자"
	  exit;;
	*) echo "잘못된 입력입니다." >&2
	  exit;;
esac

