# 프로그램 vs 프로세스
- 프로그램: 실행 가능한 파일
- 프로세스: 실행 중인 프로그램
프로그램의 인스턴스  

- 전위 프로세스: 모니터 / 키보드에 연결되어 있는 프로세스
	- 후위 프로세스: 모니터 / 키보드와 연결되어 있지 않은 프로세스
(키보드 입력을 통해 시그널을 받을 수 없다.)

# 환경 변수
	운영 체제가 사용하는 설정값
	- PATH: 프로그램의 탐색 경로
	환경변수를 업데이트 하는 방법은 export 명령을 사용하면 됩니다.

# vi(BSD) vs emacs

	이동
	h(left)
	j(down)
	k(up)
l(right)

	모드
	명령 -> 입력                  
	i: insert
	a: append
	o: 다음 줄에서 입력 모드 시작
	O: 이전 줄에서 입력 모드 시작

	입력 -> 명령
	esc

	명령 -> ex 명령 모드
	:   

	명령
복사(y)
	yy: 한줄 복사
	y$: 커서의 위치부터 문장의 끝까지
	y^: 커서의 위치부터 문장의 시작까지

잘라내기(d)
	dd: 한줄 잘라내기
	d$: 커서의 위치부터 문장의 끝까지
	d^: 커서의 위치부터 문장의 시작까지

	범위
	^: 문장의 시작
	$: 문장의 끝  
	gg: 문서의 시작
	G: 문서의 끝 

	영역 선택
	v: 한 글자 선택
	V: 한 라인 선택

붙여넣기(p)
	탐색
	이동: n 또는 N
	1. 원하는 단어로 가서  #
	2. 아래처럼 입력
	/money  

	undo: u
	redo: ctrl + r

	ex 모드
	저장: w <파일 이름>
	종료: q
	저장하면서 종료하기: wq 또는 x
	강제 종료: q!

	입력: 편집을 할 수 있는 모드
	명령: 이동, 복사, 잘라내기, 붙여넣기 등의 동작을 수행할 수 있다.
	ex: 저장, 종료, 불러오기  

	vi의 기본 셋팅
	1. ~/.vimrc - 권장
	2. ~/.exrc

	set nu  "number
	set ci  "cindent
	set si  "smartindent
	set ai  "autoindent
	set ts=4
	set sw=4


	/etc/apt/sources.list
	: 우분투의 패키지 매니저의 서버 주소
	http://kr.archive.ubuntu.com

	정규 표현식
	.: 모든 문자
	^: 시작
	$: 종료
	[]: OR
	[^a-z]: 부정을 표현하는 방법
	*: 0번 이상 반복
	+: 1번 이상 반복

	grep
	: 기본 정규 표현식을 사용할 수 있습니다.

	grep -E = egrep
	: 확장 정규 표현식을 사용할 수 있습니다.

# 패키지 관리 시스템
	A
	전통적인 방법
	1. source download
	2. 빌드
	3. 설치

	A를 설치하기 위해서는 B가 먼저 설치되어 있어야 합니다.
	=> 의존성을 해결하기 어렵다.

	Redhat: rpm
	$ yum

	Debian: deb
	$ apt-get
	$ apt


	$ sudo apt update
# 서버로부터 최신 저장소의 정보를 가져온다.

	$ sudo apt search htop
# 원하는 패키지 이름을 검색한다.

	$ sudo apt install htop
# 설치합니다.

	=> 패키지 서버가 제공하는 버전만 이용가능하다.
	: 다른 서드파티 패키지 서버를 추가해서, 설치하는 방법
	전통적인 방법으로 직접 빌드해서 사용해야 한다.


## Etc.  
	Java
	Ant -> Maven -> Gradle
	Python
	pip
	easy_install  
	Ruby
	gem




























