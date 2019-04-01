#!/bin/bash
read -p "input number: "

if [[ ! "$REPLY" =~ ^-?[0-9]+$ ]]; then
	echo "input is not an integer"
	exit 1
else
	echo "ok"
fi

