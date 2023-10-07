

#ifndef __lcd_driver
#define __lcd_driver


#include<lpc21xx.h>
#include"arm_delay.h"
#define pin_cnf   IODIR0   =  (IODIR0 & 0xFFFFFFFF) | 0xffffffff
#define lcd_in(a) IOPIN0   =  (IOPIN0 & 0xfffffc00) | (unsigned int)a <<0X2  //pin 0.2 to pino.9

#define en   (1<<12)
#define rs   (1<<10)
#define rw   (1<<11)


#define rs_data   IOSET0   =  IOSET0 | rs
#define rs_cmd    IOCLR0   =  IOCLR0 | rs
#define rw_rd     IOSET0   =  IOSET0 | rw
#define rw_wr     IOCLR0   =  IOCLR0 | rw
#define en_set    IOSET0   =  IOSET0 | en
#define en_clr    IOCLR0   =  IOCLR0 | en



void lcd_cmd(unsigned char cmd)
{
	 
pin_cnf;
en_clr;
lcd_in(cmd);
rs_cmd;
rw_wr;
en_set;
delay(100);
en_clr;	
}



void lcd_data(unsigned char data)
{
	
pin_cnf;
en_clr;
lcd_in(data);
rs_data;
rw_wr;
en_set;
delay(10);
en_clr;
}

void lcd_str(char *p)
{
	while(*p) lcd_data(*p++);
}



void lcd_init()
{
	lcd_cmd(0x01);
  lcd_cmd(0x06);
	lcd_cmd(0x0e);
	lcd_cmd(0x38);
	lcd_cmd(0x80);
}


#endif 

