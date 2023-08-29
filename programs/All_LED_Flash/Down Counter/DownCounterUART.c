/***************************************************************************************************
                                   TechhEngine
****************************************************************************************************
 * File:   main.c
 * Version: 16.0
 * Author: TechhEngine


This code has been developed and tested on boards.  
We strongly believe that the library works on any of development boards for respective controllers. 
TechhEngine DISCLAIMS ANY KIND OF HARDWARE FAILURE RESULTING OUT OF USAGE OF LIBRARIES, DIRECTLY OR
INDIRECTLY. FILES MAY BE SUBJECT TO CHANGE WITHOUT PRIOR NOTICE. THE REVISION HISTORY CONTAINS THE INFORMATION 
RELATED TO UPDATES.
 

Permission to use, copy, modify, and distribute this software and its documentation for any purpose
and without fee is hereby granted, provided that this copyright notices appear in all copies 
and that both those copyright notices and this permission notice appear in supporting documentation.
**************************************************************************************************/



/***************************************************************************************************
THIS PROGRAM DOWN COUNTS ON 4 LEDS, WHEN 'DOWN' STRING IS READ FROM UART(UART0 IN THIS CASE).
THIS PROGRAM WAS WRITTEN AND COMPILED IN KEIL4 SOFTWARE.
Add library files i.e., 'systemInit.c, uart.c, delay.c, gpio.c' along with the main program file 
(this file)to compile. And also make sure to add .h files for the respective .c files, in the folder
where you save the project file.
the above mentioned header files can be found in Library files folder from the GitHub repository
https://github.com/lucciffer/ARM-LPC2148 
THIS PROJECT IS TESTED AND VERIFIED ON SIMULATION TOOLS AND AS WELL AS BOARDS.
IN CASE OF ERRORS AND QUERIES, DROP YOUR MAIL AT: techh.engine@gmail.com
***************************************************************************************************/
#include <lpc214x.h>
#include <string.h>
#include "systemInit.h"
#include "uart.h"
#include "delay.h" 


int main() 
{	    
   char str[4]; 	//input string
   char msg[4]={"down"};	//ReF string
   int len = 0;
   int flag=0;
   int i; 
   int result; 		  //variable to store result of comparison
   SystemInit();	   
   PINSEL0=00;			  //selecting port 0
   IODIR0 |= (0xf << 18);	 //selecting pins 18-21 by shifting operation
	
   
   UART0_Init(9600); 	  //set baud rate to 9600
	
    while(1)
    {
        len = UART0_RxString(str);		 //reading string from UART
        UART0_Printf("Received String:%s   size=%2d\n\r",str,len);		  
        
		result=strncmp(msg,str,4);	   //comparing strings
		if(result==0)
		{
			flag=1;		//set flag 1 if strings are same
			break;
		}
		else
		{
			flag=0;	    //set flag 0 if strings are not same
			break;
		}
	}

if(flag == 1)
{
	
	for(i=15;i>=0;i--)	//down counter module
		{
			IOPIN0=(i << 18);
			DELAY_us(35000);
		}
}
else if(flag == 0)
{
	for(i=0;i<100;i++)
	{

	  IOPIN0=(0xff << 18);
	  DELAY_us(3500);
	  IOPIN0=0x00;
	  DELAY_us(3500);
	}
  
}
    
    
}
