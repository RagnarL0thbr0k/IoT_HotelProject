
#define RS PORTGbits.RG9
#define EN PORTGbits.RG8
#define D4 PORTDbits.RD6
#define D5 PORTDbits.RD7
#define D6 PORTDbits.RD8
#define D7 PORTDbits.RD11


#include "lcd.h"
#include <p32xxxx.h>
#include <plib.h> // Include the PIC32 Peripheral Library.
#include <xc.h>
#include <string.h>

int i;
int j=0;
unsigned int x=0;
char an[3]={'_', '-', '^'};
char an1[2]={'_', '-'};
void wait (int t)
{
    int n = t*1900;  //1900 è un numero ricavato sperimentalmente
    while(n>0) {n--;}
}
void Enable()
{
    EN=1;
    wait(1);
    EN=0;
    wait(1);
}

void LCD_Out ( char c ) {
    
    if ( c & 1 ){
        D4=1;
    }
    else {
         D4=0;
    }

    if ( c & 2 ){
        D5=1;
    }
    else {
        D5=0;
    }

    if ( c & 4 ){
        D6=1;
    }
    else {
        D6=0;
    }

    if ( c & 8 ){
        
    D7=1;
    }
    else {
        D7=0;
    }
}
void LCDCommand ( char c ) {

    RS=0;  // => RS = 
    LCD_Out((c & 0xF0) >> 4);    //Data transfer

    Enable();
    
    LCD_Out(c & 0x0F);

    Enable();

}
void LCD_displayNumber(long int number) {
  char strNumber[20];
  itoa(strNumber, number, 10);
  LCDWrite(strNumber);
}
void LCD_putc ( char c ) {

    RS=1 ;  // => RS = 1
    LCD_Out((c & 0xF0) >> 4);    //Data transfer

    Enable();
    
    LCD_Out(c & 0x0F);

    Enable();

}
void LCD_setCursor(int column, int row) {
  if(row == 1) LCDCommand(0b0010000000 + (column-1));
  if(row == 2) LCDCommand(0b0010000000 + 0x40 + (column-1));
}

LCD_Display(int on, int cursor,int blink ) {
do {                                     
    unsigned char cmd = 0x08;            
                                         
    if ( on == 1 ) {                  
        cmd |= 1 << 2;                   
    }                                    
                                         
    if ( cursor == 1 ) {              
        cmd |= 1 << 1;                   
    }                                    
                                         
    if ( blink == 1 ) {               
        cmd |= 1;                       
    }                                   
                                         
    LCDCommand(cmd);                        
} while ( 0 );
}

void initLcd()
{

    
    wait(2);
    
  // Send reset signal to the LCD
    LCDCommand(0x03);
    wait(5);
    LCDCommand(0x03);
    wait(10);
    LCDCommand(0x03);

    // Specify the data lenght to 4 bits
    LCDCommand(0x02);

    // Set interface data length to 8 bits, number of display lines to 2 and font to 5x8 dots
    LCDCommand(0x28);

    // Set cursor to move from left to right
    LCDCommand(0x06);

    LCD_Display(1, 0, 0); // Turn on display and set cursor off

    LCD_Clear();
    
}

LCDWrite(char str[])
{
    
    RS=1;
    for(i=0; str[i]!='\0';i++) 
    {
        LCD_putc(str[i]);
    }
}

void welcome()
{

    LCD_setCursor(7,1 );
    LCDWrite("HOTEL");
    LCD_setCursor(5,2 );
    LCDWrite("PINEAPPLE");
        for(j=0;j<3;j++)
    {
    LCD_setCursor(1,1 );
    LCD_putc(an[j]);
    LCD_setCursor(16,1 );
    LCD_putc(an[j]);
    wait(40);
    }
    wait(400);
}

void menu ()
{
    LCD_setCursor(6,1 );
    LCDWrite("MANUAL");
    LCD_setCursor(1,2 );
    LCDWrite("#:<mode>  *:<ok>");
    
}