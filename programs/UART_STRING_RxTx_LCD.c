
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

