#!/bin/bash

read -p "enter input: "

if [[ $REPLY =~ ^[a-z|A-Z|0-9]+$ ]]; then
	echo "Input is valid"
else
	echo "Please enter only letters and numbers"
fi
