
#include "systemInit.h"
#include "uart.h"

int main() 
{
    SystemInit();
    
    UART0_Init(9600);  // Initialize UARt at 9600 baud rate		     
    
    while(1)
    {
        UART0_TxChar('e');
    }		     
}

