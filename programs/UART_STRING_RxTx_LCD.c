/***************************************************************************************************
                                   TechhEngine
****************************************************************************************************
 * File:   main.c
 * Version: 16.0
 * Author: TechhEngine
 * Description: This file contains the program to receive and transmit string through UART and display same on LCD.  

This code has been developed and tested on TechhEngine boards.  
We strongly believe that the library works on any of development boards for respective controllers. 

 
The TechhEngine libraries and examples are licensed under the terms of the new-bsd license(two-clause bsd license).
See also: http://www.opensource.org/licenses/bsd-license.php

TechhEngine DISCLAIMS ANY KIND OF HARDWARE FAILURE RESULTING OUT OF USAGE OF LIBRARIES, DIRECTLY OR
INDIRECTLY. FILES MAY BE SUBJECT TO CHANGE WITHOUT PRIOR NOTICE. THE REVISION HISTORY CONTAINS THE INFORMATION 
RELATED TO UPDATES.
 

Permission to use, copy, modify, and distribute this software and its documentation for any purpose
and without fee is hereby granted, provided that this copyright notices appear in all copies 
and that both those copyright notices and this permission notice appear in supporting documentation.
**************************************************************************************************/
#include "systemInit.h"
#include "lcd.h"
#include "uart.h"
#include "delay.h" 


int main() 
{	    
    char str[50];  
    int len = 0;  
    SystemInit();	   
    
    /*Connect RS->P1_16, RW->P1_17, EN->P1_18 and data bus(D4:D7 - P1_20:P1_23)*/
    LCD_SetUp(P1_16,P1_17,P1_18,P_NC,P_NC,P_NC,P_NC,P1_20,P1_21,P1_22,P1_23);
    LCD_Init(2,16);
    UART0_Init(9600);
    LCD_DisplayString("Send data from  serial terminal");
    while(1)
    {
        len = UART0_RxString(str);
        UART0_Printf("Received String:%s   size=%2d\n\r",str,len);
        LCD_Clear();
        LCD_Printf("str:%s size=%2d",str,len);     
    }
    
    
}

