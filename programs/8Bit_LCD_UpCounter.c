
#include "lcd.h"
#include "systemInit.h"
#include "delay.h" 


/*
 * 
 */
int main() 
{
    int count = 0;

    SystemInit();

    /*Connect RS->P1_27, RW->P1_28, EN->P1_29 and data bus(D4:D7 - P1_16:P1_23)*/
    LCD_SetUp(P1_27,P1_28,P1_29,P1_16,P1_17,P1_18,P1_19,P1_20,P1_21,P1_22,P1_23);
    LCD_Init(4,20);
    
    LCD_DisplayString("Decimal");

    while(1)
    {
        LCD_GoToLine(1);
        LCD_Printf("Count=%4d",count);
        DELAY_ms(500);
        count++;
    }					       
}

