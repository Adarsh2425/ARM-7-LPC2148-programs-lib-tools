#include "systemInit.h"
#include "uart.h"

int main() 
{
    SystemInit();
	UART0_Init(9600);
    while(1)
    {
        UART0_Printf("Welcome to ARM Serial Programming by TechhEngine\n\r");
    }		    
}

