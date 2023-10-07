#include<lpc21xx.h>
#include "lcd_header.h"
int main()
{
    IO0DIR|=0XFFF;                // Port 0 (P0.0 - P0.11) is configured as OUTPUT
    lcd_init();                   // Call initialization function for LCD initialization
    lcd_cmd(0x8a);                // LCD command to move the cursor to a specific position
    lcd_dis("DIWALI ");           // Display the string by calling the lcd_dis function
    while(1) 
			{
				if((IO1PIN & (1<<16)) ==0)  //Check if the switch connected to P1.16 is pressed 
        lcd_cmd(0x18);              // LCD command for shifting the dispaly to the left
        delay();                    // Call Delay
			}
}