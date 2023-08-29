////Stepper motor

#include<lpc21xx.h>
void delay(unsigned int j)
{
    int i,k;
    for(i=0;i<j;i++)
    {
        for(k=0;k<9999;k++);
    }
}

int main()
{
    PINSEL1=0X00000000;		//Configure P0.16 to P0.31 as GPIO
    IODIR0=0XF0000000;		//Configure P0.28 to P0.31 as OUTPUT
    while(1)
    {
        IOSET0=0X80000000;		//ABCD->1000
        delay(10);
        IOCLR0=0XF0000000;
        
        IOSET0=0X40000000;		//ABCD->0100
        delay(10);
        IOCLR0=0XF0000000;
        
        IOSET0=0X20000000;		//ABCD->0010
        delay(10);
        IOCLR0=0XF0000000;
        
        IOSET0=0X10000000;		//ABCD->0001
        delay(10);
        IOCLR0=0XF0000000;		//OFF all 4 terminals of Stepper motor
     }
}