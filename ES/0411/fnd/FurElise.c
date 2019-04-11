#include <wiringPi.h>
#include <softTone.h>

#define SPKR 21                          /* GPIO25 */
#define TOTAL 42

#define C 261.6
#define C_l 130.8
#define Db 277.1
#define D 293.6
#define D_l 146.8
#define Eb 311.1
#define E 329.6
#define E_l 164.8
#define F 349.2
#define F_l 174.6
#define Gb 369.9
#define G 391.9
#define G_l 195.9
#define Ab 415.3
#define Ab_l 415.3
#define A 440
#define A_l 220
#define Bb 466.1
#define B 493.8
#define B_l 246.9

// Fur Elise
float notes[] = {
        E, Eb, E, Eb, E, B_l, D, C, A_l, A_l,
        C_l, E_l, A_l, B_l, B_l,
        E_l, Ab_l, B_l, C, C,
        E_l, E, Eb, E, Eb, E, B_l, D, C, A_l, A_l,
        C_l, E_l, A_l, B_l, B_l,
        E_l, C, B_l, A_l, A_l, A_l,

        B_l, C, D, E, E, E, G_l, F, E, D, D, D, F_l, E, D, C, C, C, E_l, D, C, B                                                                                                              _l, B_l,
        Eb, E, Eb, E, Eb, E, E,
        E, Eb, E, Eb, E, B_l, D, C, A_l, A_l,
        C_l, E_l, A_l, B_l, B_l,
        E_l, C, B_l, A_l, A_l, A_l, -1
};

int musicPlay()
{
        int i ;

        softToneCreate(SPKR) ;                /* 톤 출력을 위한 GPIO 설정 */

        int total = 0;

        // note 수 세기
        while (notes[total++] != -1);

        for (i = 0; i < total-1; ++i) {
                softToneWrite(SPKR, notes[i]);
                delay(280);                   /* 음의 전체 길이만큼 출력되도록                                                                                                               대기 */
        }
        return 0;
}
int main(int argc, char** argv)
{
        wiringPiSetup( ) ;

        musicPlay( );                        /* 음악 연주를 위한 함수 호출 */

        return 0;
}
