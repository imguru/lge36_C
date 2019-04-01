#!/bin/bash

read -p "input number: "

if (( $REPLY == 0 )); then 
	echo "zero"
else
	echo "non zero"
fi
