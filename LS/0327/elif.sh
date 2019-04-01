#!/bin/bash
read -p "input number: "

if [ $REPLY -gt 0 ]; then
	echo "positive"
elif [ $REPLY -lt 0 ]; then
	echo "negative"
else
	echo "same"
fi
