
#include <plib.h> // Include the PIC32 Peripheral Library.
#include <xc.h>
#include <string.h>
#include "lcd.h"
#include "dht11.h"

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
    t=t_old;
    }
}
