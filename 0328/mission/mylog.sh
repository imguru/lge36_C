#! /bin/bash
# mylog.181011

if [ -n $1 ]; then
	touch $1.`date +%H%M%S`
fi
