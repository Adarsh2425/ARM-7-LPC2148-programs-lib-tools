#include "system.h"
#include "demo.h"
#include "delay.h"
#include "gpio.h"
#include "irq.h"
#include "lcd.h"
#include "serial.h"
#include "adc.h"
#include "gsm.h"
#include "hcsr04.h"
#include "i2c.h"
#include "Nstring.h"
#include "spi.h"
#include "mcp320x.h"
#include "rtc.h"
#include "oled.h"
#include "keypad.h"
#include "dht11.h"
#include "extint.h"
#include "nrf24.h"
#include "mpu6050.h"

void mpu_example(void)
{
	  int16_t mpu_data[7];
    int temp=0;
    char str[64];
    serial0_init(9600);
    serial0_print("MPU6050 Test\r\n");
    mpu6050_init();
    while(1)
    {
        mpu6050_read(mpu_data);
        temp=(int)(mpu_data[3]/340.00+36.53);
        sprintf(str,"AcX =%d | AcY =%d | AcZ =%d | Temp =%d ",mpu_data[0],mpu_data[1],mpu_data[2],temp);
        serial0_print(str);
        serial0_print("\r\n");
        delay_ms(1000);
    }
}

void nrf_example(void)
{
	serial0_init(9600);           				//start Serial
	serial0_print("Setting Up");
	delay_ms(100);
	nrf_init();

	while(1){
		//nrf_data_integrity();
		delay_ms(1000);
	}
}

void EINT0_Handler(void) __irq
{
	EXTINT=EINT0;
	serial0_print("Interrupt \r\n");
	delay_ms(100);
	VICVectAddr = 0x00;
}

void external_int_example(void)
{
	serial0_init(9600);
	serial0_print("EINT Testing ....\r\n");
	delay_ms(100);	
	EINT_init(0,EDGE,FALLING_EDGE,(void *)EINT0_Handler);
	while(1)
	{

	}
}

void dht11_example(void)
{
	char disp[20];
	serial0_init(9600);
	serial0_print("DHT11 Testing ....\r\n");
	while(1)
	{
		dht_read11(DHT_PIN);
		serial0_print("--------------------\r\n");
		sprintf(disp,"Temperature :%d",temperature);
		serial0_print(disp);
		serial0_print("\r\n");
		sprintf(disp,"Humidity :%d",humidity);
		serial0_print(disp);
		serial0_print("\r\n");
		serial0_print("--------------------\r\n");

		delay_ms(1000);
	}
}

void keypad_example(void)
{
	uint8_t key;
	char val[16];
	serial0_init(9600);
	serial0_print("4x4 Keypad Test\r\n");

	while(1)
	{
		key=get_keypad_key();
		if(key!=0xff)
		{
			sprintf(val,"( %d ) Key Is Pressed ",key);
			serial0_print(val);
			serial0_print("\r\n");
			delay_ms(300);
		}
	}
}

void oled_example(void)
{
	oled_init();
	oled_reset();
	oled_fill(0x55);
	delay_ms(500);
	oled_clear();
	oled_fill(0x00);
	oled_print_xy(0,0,"Latest");
	oled_print_xy(0,30,"Embedded");
	while(1);
}

void rtc_example(void)
{
	char val[32];
	RTCTime rtc;
	rtc.RTC_Hour=21;rtc.RTC_Min=0;rtc.RTC_Sec=0;
	rtc_set_time(rtc);	
	serial0_init(9600);
	serial0_print("RTC Test\r\n");
	rtc_init();
	while(1)
	{
		rtc=rtc_get_time();
		sprintf(val,"Time: %d:%d:%d",rtc.RTC_Hour,rtc.RTC_Min,rtc.RTC_Sec);
		serial0_print(val);
		serial0_print("\r\n");
		delay_ms(1000);
	}
}

void mcp32_example(void)
{
	char val[32];
	uint16_t result;
	spi_init();
	serial0_init(9600);
	serial0_print("External SPI Test\r\n");

	while(1)
	{
		result=read_mcp320x(0);
		sprintf(val,"Channel 0 :%5.0d",result);
		serial0_print(val);
		serial0_print("\r\n");
		delay_ms(1000);
	}
}

void set_time_date(uint8_t *rtc_str)
{
	i2c_write_buffer(0xD0,0,rtc_str,7);
}
void hex_to_str(uint8_t value,char *str)
{
	str[0]=48+((value & 0x70)>>4);
	str[1]=48+(value & 0x0f);
}

void get_time_date(char *rtc_str)
{
	uint8_t rtc_buffer[8];
	char h_s[2];
	if (!i2c_read_buffer(0xD0,0,rtc_buffer,7))		// Read date and time from RTC 
			serial0_print("\nMemory Read error....");
  	
	
	hex_to_str(rtc_buffer[4],h_s);
	rtc_str[0]=h_s[0];rtc_str[1]=h_s[1];rtc_str[2]='/';
	hex_to_str(rtc_buffer[5],h_s);
	rtc_str[3]=h_s[0];rtc_str[4]=h_s[1];rtc_str[5]='/';
	hex_to_str(rtc_buffer[6],h_s);
	rtc_str[6]=h_s[0];rtc_str[7]=h_s[1];rtc_str[8]=' ';
	
	hex_to_str(rtc_buffer[2],h_s);
	rtc_str[9]=h_s[0];rtc_str[10]=h_s[1];rtc_str[11]=':';
	hex_to_str(rtc_buffer[1],h_s);
	rtc_str[12]=h_s[0];rtc_str[13]=h_s[1];rtc_str[14]=':';
	hex_to_str(rtc_buffer[0],h_s);
	rtc_str[15]=h_s[0];rtc_str[16]=h_s[1];rtc_str[17]=' ';
	
	if(rtc_buffer[2] > 0x12)
	{
		rtc_str[18]='P';
		rtc_str[19]='M';
	}
	else
	{
		rtc_str[18]='A';
		rtc_str[19]='M';
	}
	rtc_str[20]='\0';
}

void i2c_rtc_example(void)
{	
	serial0_init(9600);
	serial0_print("I2C RTC Testing\r\n");
	i2c_init();
	while(1)
	{
		uint8_t read_buffer[24];
		get_time_date((char *)read_buffer);
		serial0_print((char *)read_buffer);	
		serial0_print("\r\n");	
		delay_ms(1000);
	}
}

void i2c_eeprom_example(void)
{
	uint8_t write_buffer[8]="Nilesh",read_buffer[8];

	serial0_init(9600);
	serial0_print("I2C Testing\r\n");
	i2c_init();
	i2c_write_buffer(0xA0,0,write_buffer,6);
	serial0_print("Write Done\r\n");

	while(1)
	{
		if (!i2c_read_buffer(0xA0,0,read_buffer,6))		// Read date and time from RTC 
			serial0_print("\nMemory Read error....");

		serial0_print((char *)read_buffer);	
		serial0_print("\r\n");	
		delay_ms(1000);
	}
}

void hcsr04_example(void)
{
	uint32_t d=0;
	char line1[16];    

	serial0_init(9600);
	serial0_print("HCSR04 Testing\r\n");
	hcsr04_init();

	while(1)
	{
		hcsr04_trigger();
		d=get_pulse_width();

		sprintf(line1,"Distance : %d",(d/58));
		serial0_print(line1);
		serial0_print("\r\n");
		delay_ms(500);
	}
}

void gsm_example(void)
{
	char msg[30],no[15],id[2];
	char pname[10];
	serial0_init(9600);
	serial0_print("GSM Testing\r\n");

	gsm_init();
	gsm_pname(pname);
	serial0_print(pname);
	serial0_print("\r\n");
	delay_ms(2000);

	gsm_msg_send("+919960226605","GSM Testing");
	while(1)
	{
		while(gsm_wait(id)==0)
		{
			serial0_print("Waiting For Msg\r\n");
			delay_ms(200);
		}

		gsm_msg_read(no,msg,id);
		serial0_print(no);
		serial0_print("\r\n");
		serial0_print(msg);
		serial0_print("\r\n");
		delay_ms(5000);
	}
}

void adc_example(void)
{
	char ds[128];
	uint16_t adc_data1,adc_data2,adc_data3,adc_data6,adc_data7;
	adc0_init();
	serial0_init(9600);	

	while(1)
	{
		adc_data1=adc0_read(1);
		adc_data2=adc0_read(2);
		adc_data3=adc0_read(3);

		adc_data6=adc0_read(6);
		adc_data7=adc0_read(7);

		sprintf(ds,"ADC1: %5.0d ADC2: %5.0d ADC3: %5.0d ADC6: %5.0d ADC7: %5.0d",adc_data1,adc_data2,adc_data3,adc_data6,adc_data7);
		serial0_print(ds);
		serial0_print("\r\n");
		delay_ms(1000);
	}
}

void serial_example(void)
{
	serial0_init(9600);
	serial0_print("Hello LPC\r\n");
	while(1)
	{
		if(serial0_available()>0)
		{
			serial0_write(serial0_read());
		}
	}
}

void gpio_example(void)
{
	gpio_pin_mode(32,OUTPUT);

	while(1)
	{
		gpio_pin_write(32,LOW);
		delay_ms(1000);
		gpio_pin_write(32,HIGH);
		delay_ms(1000);
	}
}

void lcd_example(void)
{
	lcd_init(0,1,2,3,32,33);
	lcd_clear();
	lcd_print_xy(0,0,"#   LCP2148   #");
	lcd_print_xy(0,1,"###  Board  ###");
	while(1);
}
