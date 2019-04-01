#!/bin/bash
# 부동 소수점 연산을 위해서 bc 라는 도구를 이용합니다.

echo $(echo "scale=4; 3.14 / 3" | bc)

val1=3.14
val2=3
echo $(echo "scale=4; $val1 / $val2" | bc)

# Here Document
# <<
bc << END
scale=4
3.14 / 3
END


