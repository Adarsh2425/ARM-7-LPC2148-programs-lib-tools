/***************************************************************************************************
                                   TechhEngine
****************************************************************************************************
 * File:   main.c
 * Version: 16.0
 * Author: TechhEngine
 * Description: This file contains the program to display messages on LCD in 4-bit mode. 

This code has been developed and tested on boards.  
We strongly believe that the library works on any of development boards for respective controllers. 
C
TechhEngine DISCLAIMS ANY KIND OF HARDWARE FAILURE RESULTING OUT OF USAGE OF LIBRARIES, DIRECTLY OR
INDIRECTLY. FILES MAY BE SUBJECT TO CHANGE WITHOUT PRIOR NOTICE. THE REVISION HISTORY CONTAINS THE INFORMATION 
RELATED TO UPDATES.


   

Permission to use, copy, modify, and distribute this software and its documentation for any purpose
and without fee is hereby granted, provided that this copyright notices appear in all copies 
and that both those copyright notices and this permission notice appear in supporting documentation.
**************************************************************************************************/
#include "lcd.h"
#include "systemInit.h"

int main() 
{	   
    SystemInit(); 
		 
    /*Connect RS->P1_16, RW->P1_17, EN->P1_18 and data bus(D4:D7 - P1_20:P1_23)*/
    LCD_SetUp(P1_16,P1_17,P1_18,P_NC,P_NC,P_NC,P_NC,P1_20,P1_21,P1_22,P1_23);
    LCD_Init(2,16);
    
    LCD_DisplayString("TechhEngine");
    LCD_DisplayString("Lcd 4-bit Mode");

    while(1);
}

