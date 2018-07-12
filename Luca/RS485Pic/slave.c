// DEVCFG2
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider (1x Divider)
#pragma config FPLLMUL = MUL_20         // PLL Multiplier (24x Multiplier)
#pragma config UPLLIDIV = DIV_2         // USB PLL Input Divider (12x Divider)
#pragma config UPLLEN = OFF             // USB PLL Enable (Disabled and Bypassed)
#pragma config FPLLODIV = DIV_1         // System PLL Output Clock Divider (PLL Divide by 256)

// DEVCFG1
#pragma config FNOSC = PRIPLL           // Oscillator Selection Bits (Primary Osc w/PLL (XT+,HS+,EC+PLL))
#pragma config FSOSCEN = ON             // Secondary Oscillator Enable (Enabled)
#pragma config IESO = ON                // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = HS             // Primary Oscillator Configuration (HS osc mode)
#pragma config OSCIOFNC = ON            // CLKO Output Signal Active on the OSCO Pin (Enabled)
#pragma config FPBDIV = DIV_8           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/8)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))

// DEVCFG0
#pragma config DEBUG = OFF              // Background Debugger Enable (Debugger is disabled)
#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select (ICE EMUC2/EMUD2 pins shared with PGC2/PGD2)
#pragma config PWP = OFF                // Program Flash Write Protect (Disable)
#pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                 // Code Protect (Protection Disabled)


#define SYSCLK 80000000L // definisco la frequenza del clock
#include <p32xxxx.h>
#include <plib.h> // Include the PIC32 Peripheral Library.
#include <xc.h>
#include <stdlib.h>
#include <time.h>

//  array bidimensionale contenente i valori della ttabella
char tab[16][3];
//  array nome del dispositivo
char name[6] = {'s', 'l', 'a', 'v', 'e', '1'};
//  array che riceve i messaggi in entrata, in questo caso il nome
char data[1];
//  flag per vari utilizzi
int i, j, old_btn, value, position;
int c=0;
//  contatore di righe
int count = 0;
//  verifica caratteri del nome
int verify = 0;
//  flag per il nome è giusto
int check = 0;

 int yolo=0;

//  inizializzo il dispositivo slave
void startSlave(){
    
    old_btn = 0;
    initializeUART();
    INTEnableSystemMultiVectoredInt();
    TRISD = 0xFF;
    TRISG = 0x00;
    PORTD = 0x00;
    PORTG = 0x00;
}
void InitTimer2(){
    OpenTimer2( T2_ON | T2_SOURCE_INT | T2_PS_1_64, 0x62247);
    ConfigIntTimer2( T2_INT_ON | T2_INT_PRIOR_2);
}
//  inizializzo la tabella settando tutti i valori a 0, tranne l'indice che incrementa con il numero di righe 
//  inizializzo comunicazione UART tra PIC
void initializeUART(){
// Optimize PIC32 performance and return peripheral bus frequency
long int pbClk=SYSTEMConfig( SYSCLK, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
long int DESIRED_BAUDRATE=9600;
OpenUART1( UART_EN, UART_RX_ENABLE | UART_TX_ENABLE, pbClk/16/DESIRED_BAUDRATE-1);
ConfigIntUART1(UART_INT_PR1 | UART_RX_INT_EN);
while( BusyUART1()); // Attendo che il modulo UART sia libero
}



//  randomizzo la variabile "value" da inserire in una posizione random tra le 16 righe della tabella, setto poi il flag a '1'

void main(void) {
    
    startSlave();
    initializeUART();
    InitTimer2();
    PORTDbits.RD5=0;
    while(1)
    {
       
    }
    return;
}

void __ISR(_UART1_VECTOR, ipl1) IntUart1Handler(void)
{
    if(mU1RXGetIntFlag())
    {
        mU1RXClearIntFlag();
        
        if(DataRdyUART1())
        {   
           
           int i;
           
             data[0]= (char) getcUART1();    
             if(data[0]=='a')
           {
               PORTDbits.RD5=1;
               putcUART1('o');
                PORTDbits.RD5=0;
                data[0]==0;
               
           }
           
     
            
        }
    }
    
    if(mU1TXGetIntFlag())
    {
        mU1TXGetIntFlag();
    }
   

}

void __ISR(_TIMER_2_VECTOR, ipl2) handlesTimer2Ints(void){
    
    
// **make sure iplx matches the timer?s interrupt priority level

mT2ClearIntFlag();
// Clears the interrupt flag so that the program returns to the main loop
} // END Timer2 ISR

