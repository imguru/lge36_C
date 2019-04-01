#! /bin/bash

# ./program -f name.tar

while getopts "ali:" opt; do
	case $opt in
		a) echo "option -a"
		   option_a=1;;
		l) echo "option -l";;
		i) echo "option -i"
		   echo "ARG: $OPTARG";;

		*) echo "invalid option -$opt";;
	esac
done



