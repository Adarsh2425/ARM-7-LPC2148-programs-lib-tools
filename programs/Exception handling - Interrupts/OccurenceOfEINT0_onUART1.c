//Q.No. 4) Occurence of EINT0 on UART1
/*
Author: Abhinav Sushil Pawar
Date: 26-06-2023
Constraint: Maximum 99 interrupt counts can be displayed on UART1
*/
#include<lpc21xx.h>
#define MAX 100
unsigned char string0[]={"\nNumber of times EINT0 has occured is: "};
unsigned int count=0,tens=0;
void serial1(){
    PINSEL0=0x00050000;		//config P0.1->Rxd & P0.0->Txd (UART0)
    U1LCR=0x83;						//1000 0011 (Line control register)
    U1DLL=0x61;
    U1LCR=0x03;		
}
void send_toU1(unsigned char data){
	while(!(U1LSR&0x20)); 	  //wait till U0THR is empty
	U1THR=data;						  	//send chardata through U0THR
}
void extint0_ISR(void)__irq{
	unsigned int i=0;
	count=(count+1)%10;					//Units place
	serial1();	
	while(string0[i]!='\0'){		//Print string to UART1
		send_toU1(string0[i]);
		i++;
	}
	if(tens!=0)	send_toU1(tens+48);
	send_toU1(count+48);
	if(count==9)	tens=(tens+1)%10;			//Tens place increment
	EXTINT=0x01;							//Clear interrupt flag
	VICVectAddr=0;						//End of interrupt execution
}
int main(){
	PINSEL1=0x00000001;			//P0.16 is used as EINT0
	EXTMODE=0x01;						//Edge-sensitive mode for EINT0 [1]
	EXTPOLAR=0x01;					//Falling-edge sensitive for EINT0 [1]
	while(1){
		VICVectAddr0=(unsigned long)extint0_ISR;		//slot0 for EINT0
		VICIntEnable|=1<<14;		//Interrupt source number for EINT0=14
		VICVectCntl0=0x20|14;	//Enable slot0 & assign INT0 to slot0
	}
}

