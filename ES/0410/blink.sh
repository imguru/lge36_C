#!/bin/sh
#echo 19 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio19/direction
while true
do
	echo 1 > /sys/class/gpio/gpio19/value
	sleep 1
	echo 0 > /sys/class/gpio/gpio19/value
	sleep 1
done
