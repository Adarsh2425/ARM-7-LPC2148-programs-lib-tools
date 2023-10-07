

#ifndef _i2ccomp
#define _i2ccomp

#include <LPC213X.H>
#include"arm_delay.h"
#include"lcd_driver.h"
#define scl  (1 << 0)

#define sda  (1 << 1)
 

void i2c_init()
{
	IODIR0 = IODIR0 | 0x3;
	
}

void start_cond()
{
    //  IOCLR0  = IOCLR0 | sda;
			IOSET0  = IOSET0 | scl;
		 	delay(2);
			IOSET0  = IOSET0 | sda;
    	delay(2);
			IOCLR0  = IOCLR0 | sda;
}

void  stop_condition()
{ 
	
		IOCLR0  = IOCLR0 | scl;
	  IOCLR0  = IOCLR0 | sda;
    delay(3);	
		IOSET0  = IOSET0 | scl;
	  delay(3);
		IOSET0  = IOSET0 | sda;
 	  delay(2);
  
}

void i2c_ack()
{
			int i;
			
			IOCLR0  = IOCLR0 | scl;
		  delay(1);
			IOSET0  = IOSET0 | sda;
			 
			while(IOPIN0 >> 1 &1){i=i;}
			
	  	delay(1);
			IOSET0  = IOSET0 | scl;
	  	delay(10);	 
			IOCLR0  = IOCLR0 | scl;
		 
	
}

void i2c_write(unsigned char data)
{
   int i;
	for(i=7;i>=0;i--)
	{  
		IOCLR0  = IOCLR0 | scl;
     delay(2);
		
				if(( data >> i) & 1) 
					{	
						IOSET0  = IOSET0 | sda;
					}
				else
					{			
						IOCLR0  = IOCLR0 | sda;
					}
		
		IOSET0  = IOSET0 | scl;
	  delay(2);
}
	 
	
	IOCLR0  = IOCLR0 | scl;

 
}


unsigned char i2c_read()
{
  unsigned char data =0;
	int i;	
	
	 
	 for(i=7;i>=0;i--)
	 {  
		IOCLR0  = IOCLR0 | scl;
    delay(1);
	 	IOSET0  = IOSET0 | scl;
	  delay(2);
  	
		if(IOPIN0 & (1<<1))
		data = data | (1<<i);
  

	 }
    delay(1);
		
	 IOCLR0  = IOCLR0 | scl;
   
	
return data;	
}




void i2c_Nack()
{
	  IOCLR0  = IOCLR0 | scl;
		delay(20);
		IOSET0  = IOSET0 | scl;

	  IOSET0  = IOSET0 | sda;
	
}




#endif
