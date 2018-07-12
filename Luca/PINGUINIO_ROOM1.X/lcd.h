/* 
 * File: lcd.h
 *
 * Copyright (c) 2015 Manolis Agkopian
 * See the file LICENSE for copying permission.
 *
 * LCD library header file.
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

// Macros that correspond to LCD commands
#define LCD_Clear() LCDCommand(0x01)
#define LCD_Decrement_Cursor() LCDCommand(0x04)
#define LCD_Increment_Cursor() LCDCommand(0x05)
#define LCD_Shift_Display_Right() LCDCommand(0x06)
#define LCD_Shift_Display_Left() LCDCommand(0x07)
#define LCD_Shift_Right() LCDCommand(0x1C)
#define LCD_Shift_Left() LCDCommand(0x18)
#define LCD_Row_1() LCDCommand(0x80)
#define LCD_Row_2() LCDCommand(0xC0)



// Sets the LCD cursor position


// [Internal use only] Sets the display on/off, the cursor on/off and if it will blink or not


// [Internal use only] Sends a command to the LCD
#define LCD_Cmd( c )                     \
do {                                     \
    LCD_Write( (c & 0xF0) >> 4 );        \
    LCD_Write( c & 0x0F);                \
} while ( false )


// Prints a character on the LCD
void LCD_putc ( char a );

// Prints a string on the LCD that is allocated on the RAM
void LCD_puts ( char *a );

// Prints a string on the LCD that is allocated on the program memory
void LCD_putrs ( const char *a );

// [Internal use only] Write a byte to the LCD
void LCD_Write ( unsigned char c );

// [Internal use only] Outputs the data to the LCD Port
void LCD_Out ( char a );

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */