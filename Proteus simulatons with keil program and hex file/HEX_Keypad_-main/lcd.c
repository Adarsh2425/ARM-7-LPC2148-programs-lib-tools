/**
 * @file lcd.c
 * @author Kiran Lavu (kiranlavu9@gmail.com)
 * @brief Functions definitions for LCD module
 * @version 0.1
 * @date 2022-09-16
 * 
 * @copyright Copyright (c) 2022
 */

#include <lpc21xx.h>
#include "PinPositions.h"
#include "lcd.h"
#include "delay.h"

void lcd_init(void)
{
    IODIR0 |= (1 << RS) | (1 << RW) | (1 << EN) | (0xff << DATA);	 // configure LCD pins as output pins
    lcd_cmd(0x38); // function set,8 bit,2 line
    lcd_cmd(0x0C); // Display ON,cursor Off 
    lcd_cmd(0x01); // clear display

    IOCLR0 |= (1 << RW); // Set read only mode for LCD.	
}

void lcd_data(unsigned char d)
{
    IOCLR0 |= (0xFF << DATA); // clear the data lines
    IOSET0 |= (d << DATA); // load the data to data pins
    IOSET0 |= (1 << RS); // RS = 1 for data mode	  
    IOSET0 |= (1 << EN); // EN = 1
    delay(10);
    IOCLR0 |= (1 << EN); // EN = 0
}

void lcd_str(unsigned char *pString)
{ 
    while(*pString != '\0') // Proceed if current character is not end of string or null
    {
        lcd_data(*pString); // Display current character
	    pString++; // Point to next character and repeat
    }
}

void lcd_num(unsigned int num)
{
    lcd_num(num/10);
    lcd_data(num%10+0X30);
}

void lcd_cmd(unsigned char cmd)
{
    IOCLR0 |= (0xFF << DATA);   // clear the data lines
    IOSET0 |= (cmd << DATA);    // load the cmd to data pins
    IOCLR0 |= (1 << RS);        // RS=0 for cmd mode
    IOSET0 |= (1 << EN);		// EN=1
    delay(10);
    IOCLR0 |= (1 << EN);		// EN=0
}
