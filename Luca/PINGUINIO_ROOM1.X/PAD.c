
#include <proc/p32mx440f256h.h>



#define KP_R1        PORTGbits.RG6
#define KP_R2        PORTGbits.RG7
#define KP_R3        PORTDbits.RD5
#define KP_R4        PORTDbits.RD0
#define KP_C1        PORTBbits.RB4
#define KP_C2        PORTBbits.RB3
#define KP_C3        PORTBbits.RB2
#define KP_C4        PORTBbits.RB14
#include "pad.h"
#include "lcd.h"
#define KEYPAD_R1_DIR    TRISGbits.TRISG6
#define KEYPAD_R2_DIR    TRISGbits.TRISG7
#define KEYPAD_R3_DIR    TRISDbits.TRISD5
#define KEYPAD_R4_DIR    TRISDbits.TRISD0

#define KEYPAD_C1_DIR    TRISBbits.TRISB4
#define KEYPAD_C2_DIR    TRISBbits.TRISB3
#define KEYPAD_C3_DIR    TRISBbits.TRISB2
#define KEYPAD_C4_DIR    TRISBbits.TRISB14

void keypad_init()
{
    KEYPAD_C4_DIR = 1;
    KEYPAD_C3_DIR = 1;
    KEYPAD_C2_DIR = 1;
    KEYPAD_C1_DIR = 1;
    KEYPAD_R4_DIR = 0;
    KEYPAD_R3_DIR = 0;
    KEYPAD_R2_DIR = 0;
    KEYPAD_R1_DIR = 0;

}
char const keyPadMatrix[] =
{
    '1','2','3','A',
    '4','5','6','B',
    '7','8','9','C',
    '*','0','#','D',
    0xFF
};

char key,old_key;
int kbd_getc(){
    // This routine returns the first key found to be pressed during the scan.
    char key = 0, row;

    for( row = 0b00000001; row < 0b00010000; row <<= 1 )
    {
        {   // turn on row output
            KP_R1 = (row & 0x0001)>>0;
            KP_R2 = (row & 0x0002)>>1;
            KP_R3= (row & 0x0004)>>2;
            KP_R4 = (row & 0x0008)>>3;
            wait(1);
        }
        // read colums - break when key press detected
        if( KP_C1 )break;  key++;
        if( KP_C2 )break;  key++;
        if( KP_C3 )break;  key++;
        if(KP_C4)break;    key++;
        
     }
    KP_R1 = 0;
    KP_R2 = 0;
    KP_R3 = 0;
    KP_R4 = 0;
    if (key!=old_key){
      old_key=key;
      return keyPadMatrix[ key ];
    }
    else
    return keyPadMatrix[ 0x10 ];
}

