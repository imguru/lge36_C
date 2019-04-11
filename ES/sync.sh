#!/bin/sh
scp -r root@192.168.137.100:/root/ES/0411 .
git add .
git commit -m "."
git push
