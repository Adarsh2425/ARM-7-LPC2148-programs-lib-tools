////Keypad for 7-segment

#include<lpc21xx.h>

void delay(unsigned int j)
{
    int i,k;
    for(i=0;i<j;i++)
    {
        for(k=0;k<9999;k++);
    }
}
void disp(unsigned int i)
{
  
    unsigned int da[16]={0x003F0000,0x00060000,0x005B0000,0x004F0000,0x00660000,0x006D0000,0x007D0000,0x00070000,
												 0x007F0000,0x006F0000,0x00770000,0x007C0000,0x00390000,0x005E0000,0x00790000,0x00710000};
    IOCLR0=0x00ff0000;
    IOSET0=0x10000000;
    IOSET0=da[i];
    delay(10);
    IOCLR0=0X00FF0000;
}

int main()
{
    unsigned long int value,i;
    unsigned int row0[4]={0x00ee0000,0x00ed0000,0x00eb0000,0x00e70000};
    unsigned int row1[4]={0x00de0000,0x00dd0000,0x00db0000,0x00d70000};
    unsigned int row2[4]={0x00de0000,0x00bd0000,0x00bb0000,0x00b70000};
    unsigned int row3[4]={0x007e0000,0x007d0000,0x007b0000,0x00770000};
    PINSEL1=0x00000000;
    IODIR1 =0x00000000; 
    //IODIR0=0x30ff0000;
    IODIR0=0x000f0000;        //LED outputs P0.16to19
    IOSET0=0X000f0000;        //LED OFF

    while(1)
    {
				IOPIN1=0x00ff0000;        //Read inputs from P1.16 to 23 (Keypad)
        IOCLR1=0x00100000;
        value=IOPIN1;
        delay(10);
        value=value & 0x00ff0000;
        delay(10);
        for(i=0;i<4;i++)
        {
					if(value==row0[i])
					{
						IOCLR0=0X00010000;
            delay(10);
            IOSET0=0X00010000;
            delay(10);
            //disp(i);
            //delay(10);
					}
        }
        IO1PIN=0x00ff0000;
        IOCLR1=0x00200000;
        value=IOPIN1;
        delay(10);delay(10);
        value=value & 0x00ff0000;
        for(i=0;i<4;i++)
        {
            if(value==row1[i])
            {
							IOCLR0=0X00010000;
              delay(10);
              IOSET0=0X00010000;
              delay(10);
              //disp(i+4);
              //delay(10);
						}
        }
        IO1PIN=0x00ff0000;
        IOCLR1=0x00400000;
        value=IOPIN1;
        delay(10);
        value=value & 0x00ff0000;
        for(i=0;i<4;i++)
        {
            if(value==row2[i])
            {
							IOCLR0=0X00010000;
              delay(10);
							IOSET0=0X00010000;
							delay(10);
              //disp(i+8);
              //delay(10);
            }
        }
        IO1PIN=0x00ff0000;
        IOCLR1=0x00800000;
        value=IOPIN1;
        delay(10);
        value=value & 0x00ff0000;
        for(i=0;i<4;i++)
        {
            if(value==row3[i])
            {
              IOCLR0=0X00010000;
              delay(10);
              IOSET0=0X00010000;
              delay(10);
              //disp(i+12);
              //delay(10);
            }
        }
    }
}