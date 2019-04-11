
#include <wiringPi.h>
#include <softTone.h>

#define SPKR     21                          /* GPIO25 */
#define TOTAL  37                            /* 마리오의 전체계이름의 수 */

int notes[] = {                              /* 마리오 연주하기 위한 계이름 */
    659, 659, 659,0, 523, 659, 784,0, 523,0, 392, \
        329, 440, 494, 466, 440, 392, 659, 784, \
        880, 698, 784,0, 659, 523, 587, 494, 523, \
        392, 0, 329, 0, 440, 494, 0, 466,440
};

int musicPlay()
{
    int i ;

    softToneCreate(SPKR) ;                /* 톤 출력을 위한 GPIO 설정 */

    for (i = 0; i < TOTAL; ++i) {
        softToneWrite(SPKR, notes[i]);    /* 톤 출력 : 학교종 연주 */
    //  delay(280);                   /* 음의 전체 길이만큼 출력되도록 대기 */
        delay(270);
    }
    return 0;
}
int main(int argc, char** argv)
{
    wiringPiSetup( ) ;

    musicPlay( );                        /* 음악 연주를 위한 함수 호출 */

    return 0;
}
