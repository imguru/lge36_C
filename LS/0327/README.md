p
 $ gzip file.txt
  => file.txt.gz

   $ gzip -d file.txt.gz
    $ gunzip file.txt.gz

     ; 파일 한개에 대한 부분만 압축이 가능하다.

# tar
 : 여러 개의 파일을 하나의 파일로 묶어주는 도구

  tar c
   option
      c: 묶는다.
         x: 푼다.

         $ tar cvf hello.tar <filename1> <filename1> ...
         $ gzip hello.tar
         => hello.tar.gz

         위의 방법을 편리하게 사용하는 방법입니다.
         ```
         $ tar cvfz hello.tar.gz <filename1> <filename1> ...
         => hello.tar.gz

         bzip2
         $ tar cvfj hello.tar.bz2 <filename1> <filename1> ...
         => hello.tar.bz2

         xz
         $ tar cvf hello.tar <filename1> <filename1> ...
         $ xz hello.tar
         => hello.tar.xz

         $ tar cvfJ hello.tar <filename1> <filename1> ...
         $ xz hello.tar.xz
         ```
         압축 풀기
         $ tar xvf[zjJ] hello.tar.xz

# find
$ find . -name README.md -exec cat \{} \;
$ find . -name README.md -exec cat '{}' ';'

=> \{} or '{}' 이 검색된 결과로 치환됩니다.
=> \;  or ';'  는 exec의 마지막에 써야 하는 토큰입니다.

$ find . -name README.md -exec cp '{}' '.' ';'

# date
epoch time: 1970년 1월 1일부터 지금까지의 초타임.

03-27-2019 10:43
  
  +%m-%d-%Y %H:%M:%S

# Shell Script
1. 아래의 형태로 어떤 스크립트인지 먼저 선언해야 합니다.
   #!/bin/sh
      #!/bin/bash

      2. 실행하는 방법
        $ sh hello.sh
          $ bash hello.sh
            
              위의 처럼 사용해도 되지만, 일반적으로 스크립트 파일에 실행 권한을 부여하여 실행할 수 있습니다.
                $ chmod +x hello.sh
                  $ ./hello.sh
                    


























