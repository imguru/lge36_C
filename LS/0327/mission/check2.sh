#!/bin/bash

read -p "enter input: "

if [[ $REPLY =~ ^[1-9]{1}[0-9]{0,3}$ ]]; then
	echo "Input is valid"
else
	echo "Please enter a value between 1 and 9999"
fi
