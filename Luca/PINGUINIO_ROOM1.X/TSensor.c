
#include <plib.h> // Include the PIC32 Peripheral Library.
#include <xc.h>
#include <string.h>
#include "lcd.h"
#include "dht11.h"
int usTemp=13;
void updateTemp(int t, int t_old, int once)
{
    t= (ReadADC10(0) / 52);
    if(t!= t_old || once==1){
        once==0;
    LCD_setCursor(4,1);
    LCDWrite ("Temp: ");
    LCD_displayNumber(t);
    LCD_putc(0xDF);
    LCD_putc('C');
    LCD_setCursor(4,2);
    LCDWrite ("set:  ");
    LCD_displayNumber(usTemp);
    LCD_putc(0xDF);
    LCD_putc('C');
    if(t>usTemp){LCD_setCursor(16,1);LCD_putc('v');}
    else{ if(t<usTemp){LCD_setCursor(16,1);LCD_putc('^');}
    else{ if(t==usTemp){LCD_setCursor(16,1);LCD_putc('-');}}
    }
    t=t_old;
    }
}
