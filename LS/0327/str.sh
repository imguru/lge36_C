#!/bin/sh
# 문자열을 처리할 때도 expr 이라는 도구를 이용할 수 있습니다.

# 길이
expr length "hello"

# 문자열 안에서 특정 패턴의 인덱스를 구할 때도 사용할 수 있습니다.
# index가 1부터 시작합니다.
expr index "hello" "el"

# 부분 문자열을 추출 가능합니다.
# 2 번째 인덱스부터 길이가 3 만큼 추출.
expr substr "hello" 2 2
