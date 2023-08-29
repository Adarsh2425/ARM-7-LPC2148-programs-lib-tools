#include <LPC214X.H>

#include "gpio.h"

void gpio_pin_mode(unsigned char pin,unsigned char mode)
{
	  unsigned char _pin=pin;
    
	if(_pin<16){ 	
			PINSEL0 &=~ (3<< (_pin*2));
		}
	  else if(_pin<32){ 	
			_pin=_pin-16;
			PINSEL1 &=~ (3<< (_pin*2));
		}
		else if(_pin<48){
			_pin=_pin-32;
		  PINSEL2 &=~ (3<< (_pin*2));
		}
		
		_pin=pin;
		
		 if(_pin<32){
      
			 
			if(mode==INPUT){			
				IODIR0 &=~ (1<<_pin);
			}
			else if(mode==OUTPUT){
				IODIR0 |= (1<<_pin);
			}
		}
	  else if(_pin<48){ 	
			_pin=_pin-16;
		  
			if(mode==INPUT){			
				IODIR1 &=~ (1<<_pin);
			}
			else if(mode==OUTPUT){
				IODIR1 |= (1<<_pin);
			}
		}
		else{
			
		}

}
void gpio_pin_write(unsigned char pin,unsigned char bit_val)
{
		if(pin<32){
      
			if(bit_val==LOW){			
				IOCLR0 |= (1<<pin);
			}
			else if(bit_val==HIGH){
				IOSET0 |= (1<<pin);
			}
		}
	  else if(pin<48){ 	
			pin=pin-16;
		 if(bit_val==LOW){			
				IOCLR1 |= (1<<pin);
			}
			else if(bit_val==HIGH){
				IOSET1 |= (1<<pin);
			}
		}
		else{
			
		}
	
}

unsigned char gpio_pin_read(unsigned char pin)
{
			if(pin<32){
					return ((IOPIN0>>pin)&1);
			}
			else if(pin<48)
			{
				  pin=pin-16;
		 
					return ((IOPIN1>>pin)&1);
			}
			
return 2;
}
