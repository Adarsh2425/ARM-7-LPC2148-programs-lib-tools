/**
 * @file main.c
 * @author Kiran Lavu (kiranlavu9@gmail.com)
 * @brief Project for interfacing hex keypad
 * @version 0.1
 * @date 2022-09-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <lpc214x.h>
#include "delay.h"
#include "PinPositions.h"
#include "lcd.h"
#include "KeyPad.h"

int main()
{
    lcd_init();

	lcd_str("Keypad Init...");
    keyPad_init();
	delay(1000);

	lcd_cmd(0x01);

    while(1)
    {
        unsigned char ch = keyPad_GetKeyPressed();
        if(ch != '\0')
        {
            lcd_str("Pressed Button: ");
			lcd_data(ch);
            delay(1000);
            lcd_cmd(0x01);
        }
    }
}
