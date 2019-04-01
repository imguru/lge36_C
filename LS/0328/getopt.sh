#! /bin/bash

# ./program -ali

while getopts "ali" opt; do
	case $opt in
		a) echo "option -a"
		   option_a=1;;
		l) echo "option -l";;
		i) echo "option -i";;
		*) echo "invalid option -$opt";;
	esac
done



