#include <stdio.h>

#if 0
foo(arr);  => &arr[0] => int * 
foo(&arr); => &int[3] => int[3] * => int (*)[3] 
#endif

// 아래처럼 사용할 경우, 반드시 배열의 크기를 인자로 전달받아야 한다.
void foo(int *arr, int n) {
	int i;
	arr[0] = 10;

	printf("sizeof-foo: %ld\n", sizeof(arr));   // 8
}

void goo(int (*parr)[3]) {
	(*arr)[0] = 10;
	printf("sizeof-goo: %ld\n", sizeof(*arr));  // 12
}

// int main(int argc, char *argv[]) {
int main(int argc, char **argv) {
	int a;
	// a: int
	// 타입을 구하는 방법.
	// => 이름을 제외한 나머지가 타입이다.
	int arr[3];
	// arr: int[3]
	//  decay: 배열의 이름은 배열의 첫번째 원소의 시작 주소로 해석된다.
	//   예외
	//  1) sizeof
	//  2) &

	printf("%ld\n", sizeof(arr));
	foo(arr);
	foo(&arr);
}
