//Calculator -> single digit
/*
Author: Abhinav Sushil Pawar
Date: 19-06-2023
Constraint: Input and output, both are positive single digit integers.
operations that can be performed are: Addition(+), Subtraction(-), Multiplication(*), Division(/), Modulo(%)
*/
#include<lpc21xx.h>
void serial()
{
    PINSEL0=0x00000005;		//[0101]	config P0.1->RxD(UART0)[01], and P0.0->TxD(UART0)[01]
    U0LCR=0x83;						//1000 0011 (Line control register)
    U0DLL=0x61;
    U0LCR=0x03;	
}
void delay()
{
    int i;
    for(i=0;i<100;i++);
}
int main()
{
    unsigned int ans,op1,op2;
    unsigned char operation;
    serial();

		while(!(U0LSR&0x01));           //Receive
    op1=U0RBR;
    U0THR=op1;
	
		while(!(U0LSR&0x01));		        //Receive
    operation=U0RBR;
    U0THR=operation;
    
    while(!(U0LSR&0x01));            //Receive
    op2=U0RBR;
    U0THR=op2;
                        
    while(!(U0LSR&0x20));            //Transmit    
    U0THR='=';
    delay();
    
    switch(operation)
    {
        case '+': ans=(op1-48)+(op2-48); //48 is the ASCII of zero
                  break;
        case '-': ans=(op1-48)-(op2-48);
                  break;
        case '*': ans=(op1-48)*(op2-48);
                  break;
        case '/': ans=(op1-48)/(op2-48);
                  break;
        case '%': ans=(op1-48)%(op2-48);
                  break;
    }
    while(!(U0LSR&0x20));                //Transmit    
    U0THR=ans+48;
    delay();
    
    while(!(U0LSR&0x20));                //Transmit    
    U0THR='\n';
    delay();
}
