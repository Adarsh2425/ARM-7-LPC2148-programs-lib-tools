

#ifndef __i2c_frame_comp
#define __i2c_frame_comp

#include <LPC213X.H>
#include"arm_delay.h"
#include"lcd_driver.h"

#define scl  (1 << 0)
#define sda  (1 << 1)
#define given_delay 10

void i2c_init()
{
	IODIR0 = IODIR0 | 0x3;
	
}

void start_cond()
{
      IOCLR0  = IOCLR0 | scl;
			delay(given_delay);
	    IOSET0  = IOSET0 | sda;
    	delay(2);
    	IOSET0  = IOSET0 | scl;
		 	delay(given_delay);
			IOCLR0  = IOCLR0 | sda;
	    delay(given_delay);
			  
}

void  stop_condition()
{ 
	
		IOCLR0  = IOCLR0 | scl;
	  delay(given_delay);	
	  IOCLR0  = IOCLR0 | sda;
    delay(given_delay);	
		IOSET0  = IOSET0 | scl;
	  delay(given_delay);
		IOSET0  = IOSET0 | sda;
 	  delay(given_delay);
    IOCLR0  = IOCLR0 | scl;
}

void i2c_ack()
{
    	IOCLR0  = IOCLR0 | scl;
		  delay(given_delay);
			IOSET0  = IOSET0 | sda;
			 
			while(IOPIN0 >> 1 &1){}
			
	  	delay(given_delay);
			IOSET0  = IOSET0 | scl;
	  	delay(given_delay);	 
			IOCLR0  = IOCLR0 | scl;
		 
	
}

void i2c_write(unsigned char data)
{
   int i;
	for(i=7;i>=0;i--)
	{  
			IOCLR0  = IOCLR0 | scl;
			delay(given_delay);
		
				if(( data >> i) & 1) 
					{	
						IOSET0  = IOSET0 | sda;
					}
				else
					{			
						IOCLR0  = IOCLR0 | sda;
					}
		delay(given_delay);
		IOSET0  = IOSET0 | scl;
	  delay(given_delay);
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
    delay(given_delay);
	 	IOSET0  = IOSET0 | scl;
	  delay(given_delay);
  	
		if(IOPIN0 & (1<<1))
		data = data | (1<<i);
   }
   
	 IOCLR0  = IOCLR0 | scl;
   
	 return data;	
}


void i2c_Nack()
{
	  IOCLR0  = IOCLR0 | scl;
		delay(given_delay);
		IOSET0  = IOSET0 | scl;
    delay(given_delay);
	  IOSET0  = IOSET0 | sda;
	
}




#endif
