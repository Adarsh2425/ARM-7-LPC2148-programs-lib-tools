#include <LPC213X.H>
#include"arm_delay.h"
#include"lcd_driver.h"
#include"i2c_device_driver.h"

int main()
{
  
	
	unsigned char  i ;
	PINSEL0 = 0x00000000;
	IODIR0 = 0xffffffff;

	lcd_init();
	
/*
ic -> ds1338c
dev_addr = 0xD0
*/
device_write(0xd0,00,'a');  //device with 0xd0 address and word addr 0x00
lcd_data(device_read(0xd0,00));
	

/*
ic -> 24aa01 (memory ic)
dev_addr = 0xa0
*/	
device_write(0xa0,00,'b');  //device with 0xa0 address and word addr 0x00
lcd_data(device_read(0xa0,00));
	
	
	while(1);
	return 0;
}
