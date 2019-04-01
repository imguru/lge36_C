#!/bin/bash
read -p "input number: "

if [ $REPLY -eq 0 ]
then
	echo "number is zero"
else
	echo "number is not zero"
fi
