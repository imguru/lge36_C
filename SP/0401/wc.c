#include <stdio.h>

// wc filename
int main( int argc, char **argv )
{
	FILE *fp;
	int ch;
	int flag=0;
	int line=0, char_cnt=0, word_cnt=0;
	int width;
	fp = fopen(argv[1], "r");

	while( (ch = fgetc( fp )) != EOF )
	{
		char_cnt++;
		if( ch == '\n')   // 라인수는 '\n'의 개수이다. 
			++line;

		if( ch!='\n' && ch!=' ' && ch!='\t' ) // 공백 문자가 아니라면
		{
			if( flag == 0 ) // 단어수는 단어의 첫 글자에서만 계수
			{
				word_cnt++; 
				flag = 1;
			}
		}
		else
		{
			flag = 0;
		}
	}
	width=4;     // %*d, width는 가변적인 align을 변수를 사용하여 구현가능 
	printf("%*d %*d %*d %s\n", 
			width, line, width, word_cnt, width, char_cnt, argv[1] );
	fclose(fp);
	return 0;
}

			

