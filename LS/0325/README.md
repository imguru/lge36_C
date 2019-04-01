

/home/linux

상대 경로
  : 현재 작업 디렉토리를 기준으로 이동하는 경로
 . : 현재 작업 디렉토리
 ..: 부모 디렉토리

 $ cd ..
 :/home $

절대 경로
  : root(/)를 기준으로 이동하는 경로

숨김 파일
  : .으로 시작하는 이름을 가진 파일이나 디렉토리
 리눅스는 디렉토리를 새롭게 생성하면, ., ..을 자동으로 만들어준다.

            소유자    그룹    Other
d            rwx    rwx     r-x
             111    111     101
             rwx    rwx     ---
파일의 종류     0770
d: 디렉토리
-: 일반파일

touch: 없는 파일이면, 새롭게 생성하고, 존재하면 수정 시간을 
       업데이트 한다.
$ cat > output.txt
> - 리다이렉션
cat 프로세스의 표준 출력을 output.txt의 파일로
변경해준다.
EOF: Ctrl + D


UTF-8(*)
UTF-16 / cp949(euc-kr)

Unix 
Linux
  => POSIX

하드 링크
  ln a.txt b.txt
 한계
   1. 같은 파일 시스템에서만 사용할 수 있다.
   2. 디렉토리에 대해서 생성하는 것이 불가능하다.

심볼릭 링크
   1. 데이터 블록을 참조하는 것이 아니라, 경로를 가지고 있다.
   2. 파일의 종류를 심볼릭 링크로 구분하고 있기 때문에,
      디렉토리에 대해서 사용하는 것을 허용한다.

Linux
  stdin(키보드) - 0
      $ ./a.out < input.txt

  stdout(모니터) - 1
      $ ./a.out > output.txt
      $ ./a.out >> output.txt

  stderr(모니터) - 2
  	  $ ./a.out 2> output.txt

  stdout & stderr
      $ ./a.out > stdout.txt 2> stderr.txt < input.txt

           $ ./a.out &> output.txt
      (권장)$ ./a.out >& output.txt

      $ ./a.out > output.txt 2>&1
      $ ./a.out 2> error.txt 1>&2

  리눅스 커널이 부팅할 때, 최초의 프로세스(init 프로세스)가 3개의 파일을
  연다.
    stdin
    stdout
    stderr

  리눅스 파이프
    1) 익명 파이프
       ls | sort
       ; ls의 표준 출력 결과를 sort의 표준 입력으로 리다이렉션.

    2) 이름있는 파이프 - mkfifo
