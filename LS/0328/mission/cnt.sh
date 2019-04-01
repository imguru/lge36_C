#!/bin/sh
file_count=`find . -maxdepth 1 -type f | egrep -v "(^\./\.)|\.$" | wc -l`
dir_count=`find . -maxdepth 1 -type d | egrep -v "(^\./\.)|\.$" | wc -l`

echo "파일 수:$file_count 디렉토리 수: $dir_count"
