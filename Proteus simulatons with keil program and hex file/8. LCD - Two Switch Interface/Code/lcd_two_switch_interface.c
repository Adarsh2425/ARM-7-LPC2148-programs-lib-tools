#include<lpc21xx.h>
#include <stdlib.h>
#include "lcd_header.h"

int main()
{
	IO0DIR|=0XFFF;                      // Port 0 (P0.0 - P0.11) is configured as OUTPUT
	int j=0;                            //Initialize an integer variable
	char val_j[3];                      //Initialize a character array
	lcd_init();                         //Call LCD initialization function
	lcd_dis("Count : ");                //Display the string on LCD
	lcd_cmd(0xC0);	                    //Force cursor to the beginning of the second line
	sprintf(val_j,"%d ",j);             //Writes a formatted string to a variable   
	lcd_dis(val_j);	                    // Display the initial count value on the LCD i.e.count=0
while(1)
{
	  if((IO1PIN & (1<<16)) ==0)        //check if the increment button is pressed
	     {	
         lcd_cmd(0xC0);			          //Force cursor to the beginning of the second line	 
	       sprintf(val_j,"%d ",++j);    //Increment the count
		     lcd_dis(val_j);	            // Display the count value on LCD
		     delay(100);                  // Call Delay
		     lcd_cmd(0xCC);
			 }
	   else if((IO1PIN & (1<<17)) ==0)   //check if the decrement button is pressed
	     {	
         lcd_cmd(0xC0);				 
	       sprintf(val_j,"%d ",--j);      //Writes a formatted string to a variable
		     lcd_dis(val_j);	              // Display the count value on LCD
		     delay(100);                    //Call Delay
		     lcd_cmd(0xCC);
			 }
	}return 0;
}

