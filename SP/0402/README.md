특수 퍼미션
1. set user id bit
2. set group id bit
3. sticky bit

000 110 100 100
rw- r-- r--
	100

Set User Id bit(User)
	rw-  -> rwS
	rwx  -> rws

	일반적으로 프로세스의 권한(Effective User ID)은
	프로그램을 실행시킨 사용자의 권한과 동일하게 설정된다.
	하지만 프로그램에 Set-User-Id-Bit가 설정되어 있다면
	프로그램의 소유자 권한으로 프로세스의 권한을 설정한다.

	010
Set Group Id bit(Group)
	rw-  -> rwS
	rwx  -> rws

	001
Sticky bit(Other)
	rw-  -> rwT
	rwx  -> rwt
	
	디렉토리의 w 권한은 파일을 삭제할 수 있다.
	만약 Sticky bit가 설정되어 있다면, 오직 파일의 소유자만이 자신의 파일을 삭제하는 것이 가능하다.











