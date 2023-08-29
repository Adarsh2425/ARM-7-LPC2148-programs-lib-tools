#include "system.h"
#include "i2c.h"

static uint8_t dev_addr;
void i2c_init (void)
{
		// Power on I2C0 peripheral
		PCONP	|= 0x00000080;
		// Define port pin as SDA and SCL
		PINSEL0	|= 0x00000050 ;
		
	  I20CONCLR	= 0x6C;	// clear all I2C config bits
		I20CONSET	= 0x40;	// set I2EN
		// I2C Clock Duty Cycle (high and low), 100KHz
		I20SCLH 	= 50;
		I20SCLL 	= 50;
}

uint8_t i2c_start (void)
{
		I20CONSET	= 0x20;			// Start set
		if (!i2c_wait_status(0x08))		// 0x08: ready for device address
			return FALSE;

		return TRUE;
}

uint8_t i2c_restart (void)
{
		I20CONCLR	= 0x08;			// clear SI flag
		I20CONSET	= 0x10;			// generate stop condition

		i2c_start();
		return TRUE;
}

uint8_t i2c_write(uint8_t data,uint8_t status_cmd)
{
		I20DAT		= data;												// addr[0]=0 means I2C write
		I20CONCLR	= 0x2C;												// clear all except I2EN
		if (!i2c_wait_status(status_cmd))				// 0x18: ready for data byte
			return FALSE;

		return TRUE;
}

uint8_t i2c_read(void)
{
		I20DAT		= dev_addr|0x01;			// addr[0]=1 means I2C read
		I20CONCLR	= 0x28;									// clear all except I2EN and AA
		if (!i2c_wait_status(0x40))				// 0x40: ready for data byte
			return FALSE;			
	
		I20CONCLR	= 0x2C;									// clear all except I2EN 
		if (!i2c_wait_status(0x58))				// 0x58: data byte received return ACK
			return FALSE;

	return (uint8_t)I20DAT;
}

void i2c_stop (void)
{
		I20CONSET	= 0x10;			// generate stop condition	
		I20CONCLR	= 0x2C;
}

uint8_t i2c_wait_status (uint8_t u8status)
{	
	//while(I20STAT != u8status){}
  uint32_t t_out=0;
  while (t_out < 1000) 
	{
		  delay_ms(1);t_out++;
			if (I20CONSET & 8) // poll SI bit
			{
				if (I20STAT == u8status)
				{
					return TRUE;
				}
		}
	}
return FALSE;	
}

uint8_t i2c_read_buffer (uint8_t device_addr,uint8_t u32startAddr, uint8_t *u8ptr2arr, unsigned int u32len)
{
		unsigned int	u32i;
		dev_addr=device_addr;
	  for (u32i=0;u32i<u32len;u32i++)
		{
				i2c_start ();
				i2c_write(device_addr,0x18);
				i2c_write(u32startAddr & 0x000000FF,0x28);
				i2c_restart ();	
				u8ptr2arr[u32i]	= i2c_read();
				i2c_stop();
				u32startAddr++;		
		}
		return TRUE;
}

uint8_t i2c_write_buffer (uint8_t device_addr,uint8_t u32startAddr, uint8_t *u8ptr2arr, unsigned int u32len)
{
		unsigned int	u32i;
		i2c_start ();
		i2c_write(device_addr,0x18);
		i2c_write(u32startAddr & 0x000000FF,0x28);
		
		for (u32i = 0; u32i < u32len; u32i++)
		{		
				i2c_write((*(u8ptr2arr+u32i)&0x000000FF),0x28);
				u32startAddr++;
		}	
		
		i2c_stop();
		return TRUE;
}
