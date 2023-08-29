/***************************************************************************************************
                                   TechhEngine
****************************************************************************************************
 * File:   main.c
 * Version: 16.0
 * Author: TechhEngine
 * Description: This file contains the program to display messages on LCD in 8-bit mode. 

This code has been developed and tested on boards.  
We strongly believe that the library works on any of development boards for respective controllers. 

TECHHENGINE DISCLAIMS ANY KIND OF HARDWARE FAILURE RESULTING OUT OF USAGE OF LIBRARIES, DIRECTLY OR
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
		 
    /*Connect RS->P1_27, RW->P1_28, EN->P1_29 and data bus(D4:D7 - P1_16:P1_23)*/
    LCD_SetUp(P1_27,P1_28,P1_29,P1_16,P1_17,P1_18,P1_19,P1_20,P1_21,P1_22,P1_23);
    LCD_Init(2,16);
    
    LCD_DisplayString("TechhEngine");
    LCD_DisplayString("Lcd 8-bit Mode");

    while(1);
}
