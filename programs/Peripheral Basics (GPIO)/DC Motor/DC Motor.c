////DC Motor

#include<lpc21xx.h>
void delay(unsigned int constant)
{
    int i,k;
    for(i=0;i<constant;i++)
    {
        for(k=0;k<9999;k++);
    }
}
void clockwise()
{
    IOSET0=0X00000C00;		//P0.10->HIGH & P0.11->HIGH (Stop)
    delay(10);
    IOCLR0=0X00000400;		//P0.10->HIGH & P0.11->LOW	(Clockwise)
    delay(10);
}
void anticlock()
{
    IOSET0=0X00000C00;		//P0.10->HIGH & P0.11->HIGH	(Stop)
    delay(10);
    IOCLR0=0X00000800;		//P0.10->LOW & P0.11->HIGH	(AntiClockwise)
		delay(10);
}

int main()
{
    unsigned int i;
    PINSEL0=0X00000000;			//Configure P0.0 to P0.15 as GPIO
    IODIR0=0X00000C00;			//Configure P0.11 & P0.10 as Output
    
    while(1)
    {
                for(i=0;i<99999;i++)
                for(i=0;i<99999;i++)
                for(i=0;i<99999;i++)
                anticlock(); 

                for(i=0;i<99999;i++)
                for(i=0;i<99999;i++)
                for(i=0;i<99999;i++)
                clockwise();     
    }
}