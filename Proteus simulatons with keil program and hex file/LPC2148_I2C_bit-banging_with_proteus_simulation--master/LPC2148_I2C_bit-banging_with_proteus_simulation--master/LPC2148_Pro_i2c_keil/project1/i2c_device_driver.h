#ifndef __i2c_device_driver
#define __i2c_device_driver


#include"i2c_frame_comp.h"
#include"lcd_driver.h"

unsigned char device_read(unsigned char dev_addr,unsigned char word_addr)
{
	unsigned char data =0x00;;
	
		i2c_init();
	  start_cond();
		i2c_write(dev_addr);
		i2c_ack();
		i2c_write(word_addr);
  	i2c_ack();
    start_cond(); 
		i2c_write(dev_addr|0x01);
   	i2c_ack();
		data =  i2c_read();
		i2c_Nack();
		stop_condition();
	 
	return data;
}
void  device_write(unsigned char dev_addr,unsigned char word_addr,unsigned char data)
{			
			 
			i2c_init();
			start_cond();
			i2c_write(dev_addr);
			i2c_ack();
	 	 	i2c_write(word_addr);
			i2c_ack();
			i2c_write(data);
			i2c_ack();
			stop_condition();
	
	return ;
	
}











#endif
