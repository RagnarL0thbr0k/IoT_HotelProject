#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
// Use project enums instead of #define for ON and OFF.


#define SYSCLK 80000000L // definisco la frequenza del clock
#include <p32xxxx.h>
#include "lcd.h"
#include <plib.h> // Include the PIC32 Peripheral Library.
#include <xc.h>
#include <string.h>
#include "pad.h"
#define CONFIG1 (ADC_MODULE_ON | ADC_FORMAT_INTG32 | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_ON)
#define CONFIG2 (ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_ON | ADC_SAMPLES_PER_INT_1 | ADC_ALT_BUF_OFF | ADC_ALT_INPUT_OFF)
#define CONFIG3 (ADC_CONV_CLK_INTERNAL_RC | ADC_SAMPLE_TIME_15)
#define CONFIGPORT (ENABLE_AN1_ANA)
#define CONFIGSCAN (SKIP_SCAN_AN0 | SKIP_SCAN_AN15 | SKIP_SCAN_AN2 | SKIP_SCAN_AN3 | SKIP_SCAN_AN4 | SKIP_SCAN_AN5 | SKIP_SCAN_AN6 | SKIP_SCAN_AN7 | SKIP_SCAN_AN8 | SKIP_SCAN_AN9 | SKIP_SCAN_AN10 | SKIP_SCAN_AN11 | SKIP_SCAN_AN12 | SKIP_SCAN_AN13 | SKIP_SCAN_AN14)
#define LED PORTDbits.RD10
    int c=0;
    int a=0;
    int o=0;
    int s=0;
    int m=0;
    int u=0;   //indice per inserimento psw[]
    int check=0;
    
    char psw[5]={0,0,0,0,0};
    char psw1[5]={'A','B','C','6','5'};
    unsigned int startClock=0;
    char ora[2]={0,0};
    char min[2]={0,0};
    char sec[2]={0,0};
    char keypress,keyboard='0';
    
    int once=1;
void InitTimer2(){
    OpenTimer2( T2_ON | T2_SOURCE_INT | T2_PS_1_64, 0x62247);
    ConfigIntTimer2( T2_INT_ON | T2_INT_PRIOR_2);
}
void initClock()
{   LCD_setCursor(1,1);
    LCDWrite("Set current time");
     LCD_setCursor(7,2);
     LCD_putc(':');
     LCD_setCursor(10,2);
     LCD_putc(':');
     
}
void setClock(char keypress)
{   

    keypress = kbd_getc();
                if(keypress!='ÿ' && keypress!='A'&& keypress!='B'&& keypress!='C'&& keypress!='D'&& keypress!='#')
                {
                        a++;
                        once=1;
                        if(a>6)a=1;
                }

           switch(a)
           {
               case 1: if(once==1){ once=0; ora[0]=keypress; LCD_setCursor(5,2); LCD_putc(keypress);}
               break;
               case 2:  if(once==1){ once=0; ora[1]=keypress; o=atoi(ora); LCD_putc(keypress); if(o>23){o=23;LCD_setCursor(5,2);LCD_displayNumber(o);}}
               break;
               case 3: if(once==1){ once=0; min[0]=keypress; LCD_setCursor(8,2); LCD_putc(keypress);}
               break;
               case 4:  if(once==1){ once=0; min[1]=keypress; m=atoi(min); LCD_putc(keypress); if(m>59){m=59;LCD_setCursor(8,2);LCD_displayNumber(m);}}
               break;
               case 5: if(once==1){ once=0; sec[0]=keypress; LCD_setCursor(11,2); LCD_putc(keypress);}
               break;
               case 6:  if(once==1){ once=0; sec[1]=keypress; s=atoi(sec); LCD_putc(keypress); if(s>59){s=59;LCD_setCursor(11,2);LCD_displayNumber(s);}}
               break;
           }
}
void updateClock(){
    if(c>=7) {
        PORTBbits.RB13=~PORTBbits.RB13;
        s++; 
        c=0;    
        if(s==60)
        {
            s=0;
            m++;
            if(m==60)
            {
                m=0; 
                o++;
                if(o>=24)o=0; 
                }
            }
        }
    
    }
void viewClock(){
    
    LCD_setCursor(5,1);
    if(o<10)LCD_displayNumber(0);
    LCD_displayNumber(o);
    LCD_putc(':');
    if(m<10)LCD_displayNumber(0);
    LCD_displayNumber(m);
    LCD_putc(':');
    if(s<10)LCD_displayNumber(0);
    LCD_displayNumber(s);
}
void checkPsw(char psw[])
{
    if(psw[0]==psw1[0] && psw[1]==psw1[1] && psw[2]==psw1[2] && psw[3]==psw1[3] && psw[4]==psw1[4] ){
        check=1; 
        LCD_setCursor(16,2);
        LCDWrite("V");
        wait(50);
        
    }
    else
    {
        LCD_setCursor(16,2);
        LCDWrite("X");
    }
}
void Password(char psw[])
{   u=0;
    LCD_setCursor(1,5);
   LCDWrite("PASSWORD:");
   LCD_setCursor(1,2);
   LCDWrite("*:<ok>");
   LCD_setCursor(10,1);
   
    while(check==0){  
        
        keypress = kbd_getc();
         if(keypress!='ÿ'&& keypress!='#' )
            {
            if(keypress=='*')checkPsw(psw);
            psw[u]=keypress;
            LCD_putc(psw[u]);
            u++;
            if(u>4)
            {
                u=0; 
                LCD_setCursor(10,1); 
            }
            
            
            }
    
        
    }
}


void initializeADC(){
    CloseADC10(); // Generally, you should disable the ADC before setup. 
    // Use ground as negative reference for channel A instead of pin AN1 (RB1)
    SetChanADC10( ADC_CH0_NEG_SAMPLEA_NVREF);
    OpenADC10( CONFIG1, CONFIG2, CONFIG3, CONFIGPORT, CONFIGSCAN);
    // Setup for the ADC10.
    EnableADC10(); // Enables the ADC10.
}
int main(void)
{

    

    
    TRISDbits.TRISD6=0;
    TRISDbits.TRISD7=0;
    TRISDbits.TRISD8=0;
    TRISDbits.TRISD11=0;
    TRISGbits.TRISG9=0;
    TRISGbits.TRISG8=0;
    TRISBbits.TRISB13=0;
    
    TRISBbits.TRISB8=1;
    TRISBbits.TRISB9=1;
    TRISDbits.TRISD9=0;
    TRISDbits.TRISD10=0;
    mPORTDSetPinsDigitalOut(BIT_9 | BIT_10);
    mPORTBSetPinsDigitalOut(BIT_2);
    mPORTBSetPinsDigitalOut(BIT_14 | BIT_13);
    mPORTBSetPinsDigitalOut(BIT_3 | BIT_4);
    SYSTEMConfigPerformance(SYSCLK);
    INTEnableSystemMultiVectoredInt();
    initializeADC();
    InitTimer2();
    int i=0;
    initLcd();
    char pw[4];
    int t=0;
    int t_old; 
    keypad_init();
    
    welcome();
    LCD_Clear();
    Password( psw);
    LCD_Clear();
    // Use multi-vectored interrupts
    while(1)
    {   
        if(startClock)updateClock();
        keypress = kbd_getc();
             if(keypress!='ÿ')
             {
                 
                 if(keypress == '#') 
                 {
                     once=1;
                     i++;
                     if(i>3)i=2;
                     
                 }
             }
        
        switch(i)
        {   
            case 0: if(once==1){LCD_Clear(); once=0; menu();}
            break;
            case 1:  if(once==1){LCD_Clear(); once=0; initClock();} setClock(keypress);
            break;
            case 2: if(once==1){LCD_Clear(); once=0; startClock=1; }updateTemp(t,t_old);
            break;
            case 3: if(once==1){LCD_Clear(); once=0;} viewClock();
            break;
        }
        
    
         
 
    }
  
    
    return 1;
}

void __ISR(_TIMER_2_VECTOR, ipl2) handlesTimer2Ints(void){
    c++;
    LED=0;
// **make sure iplx matches the timer?s interrupt priority level

mT2ClearIntFlag();
// Clears the interrupt flag so that the program returns to the main loop
} // END Timer2 ISR

