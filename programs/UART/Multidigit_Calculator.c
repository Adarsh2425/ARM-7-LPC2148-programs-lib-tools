//Calculator -> Multiple digits
/*
Author: Abhinav Sushil Pawar
Date: 20-06-2023
Constraint: Input and output, both are positive integers (of MAX=6 digits).
operations that can be performed are: Addition(+), Subtraction(-), Multiplication(*), Division(/), Modulo(%), power(^)
*/
#include<lpc21xx.h>
#define MAX 6				//Maximum digit
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
void sendDigit(unsigned int data)
{
	//U0LSR.5->Transmit holding register empty (0->U0THR has valid data; 1=>U0THR empty) 
	while(!(U0LSR&0x20)); 	  //wait till U0THR is empty
	U0THR=data+48;						//48 is the ASCII of zero	//send chardata through UOTHR
	delay();
}
unsigned int receiveASCII()
{
	unsigned int data;
	//U0LSR.0->Receiver data ready (0=>U0RBR is empty; 1=>U0RBR contains valid data)
	while(!(U0LSR&0x01));  //Receive		//wait till U0RBR contains valid data
	data=U0RBR;				//copy received data in a variable
	return data;
}
int main()
{
	while(1)
	{    
		unsigned int i,temp,rem,rev,zcount=0;
		unsigned int op1=0,op2=0,ans=0;
    unsigned char operation;
    serial();

		for(i=0;i<MAX;i++)
		{
			temp=receiveASCII()-48;
			if(!(temp>=0 && temp<=9))			//if entered character is not a number
				break;
			U0THR=temp+48;
			op1=op1*10+temp;
		}	
  
		operation=temp+48;
		U0THR=operation;
	
		for(i=0;i<MAX;i++)
		{
			temp=receiveASCII()-48;
			if(!(temp>=0 && temp<=9))			//if entered character is not a number
				break;
			U0THR=temp+48;
			op2=op2*10+temp;					//48 is the ASCII of zero
		}	                    
  
		while(!(U0LSR&0x20));            //Transmit    
		U0THR='=';
		delay();
			
		switch(operation)
		{
			case '+': ans=op1+op2; 
                break;
      case '-': ans=op1-op2;
								break;
      case '*': ans=op1*op2;
                break;
      case '/': ans=op1/op2;
								if(op2==0){
									sendASCII('e');
									sendASCII('r');
									sendASCII('r');
									sendASCII('o');
									sendASCII('r');
									sendASCII('\n');
									continue;
								}
                break;
      case '%': ans=op1%op2;
                break;
		  case '^': ans=op1;
			 					for(i=1;i<op2;i++)	ans=ans*op1;
								break;
		}
		if(ans==0)
			sendDigit(0);
		//Reverse the ans digits
		rev=0;
		while(ans!=0)				//reverse the number ans
		{
			rem=ans%10;
			ans=ans/10;
			rev=rev*10+rem;
			if(rev==0)	zcount++;		//if lower digits of ans are zeros
		}
		//send digits one-by-one from LSD to MSD of reversed ans
		while(rev!=0)
		{
			temp=rev%10;
			rev=rev/10;
			sendDigit(temp);
		}
		for(i=0;i<zcount;i++)		//append zeros at end if exits
			sendDigit(0);
		//Print next line	
		while(!(U0LSR&0x20));                //Transmit    
		U0THR='\n';						//next line 
		delay();
	}
}
