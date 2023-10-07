#include<lpc21xx.h>
#include "lcd_header.h"
int main()
{
    IO0DIR|=0xFFF;                  // Port 0 (P0.0 - P0.11) is configured as OUTPUT
    lcd_init();                     // Call initialization function for LCD initialization
    lcd_dis("Embedded Systems");    // Display the string by calling the lcd_dis function
    while(1) 
		{
        delay(10);                 //Call Delay
    }
		return 0;
}