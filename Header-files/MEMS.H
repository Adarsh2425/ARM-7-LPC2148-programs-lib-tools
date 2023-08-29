char memsdata;

void i2c_delay(unsigned int val)			  //DELAY FUNCTION FOR I2C
{
 unsigned int i2c_i,i2c_j; 
 for(i2c_i=0;i2c_i<val;i2c_i++)
 for(i2c_j=0;i2c_j<1000;i2c_j++);
}

/*void delay(unsigned long int count1)
{
  while(count1 > 0) {count1--;}							// Loop Decrease Counter	
}*/

void i2c_lpc_init(int Mode)							//I2C INITILIZATION
{
  PINSEL0 |=0x50; 
  IODIR0 = 0x0C;  /* set port 0.2 and port 0.3 to output, high */   
  IOSET0 = 0x0C; 
  
  if(Mode == '1')	 //200 
  {
  //--- I2C Timing for 58 MHz (t = 16.954 ns) ---
      I2C0SCLH = 75;  //-- more then 0.6 us  - 0.8
      I2C0SCLL = 75;  //-- more then 1.3 us  - 1.4
   }
   else //Slow
   {
      I2C0SCLH = 150;//SCHL*4;  
      I2C0SCLL = 150;//SCHL*4;
   }

   I2C0CONCLR = 0xFF;           //-- Clear all flags
   I2C0CONSET = 0x40;           //-- Set Master Mode  --- Enable I2C  
}
//---------------------------------------------------------------------------
static int i2c_lpc_ctrl(int ctrl)
{
 //-- Set START
 I2C0CONCLR = 0xFF; // Clear all bits
 I2C0CONSET |= (1<<6)| (1<<5);
 while(!(I2C0CONSET & (1<<3)));      //--- End START	 
 //-- Set ADDRESS
 I2C0DAT = ctrl;
 I2C0CONCLR = (1<<5) | (1<<3); //-- Clear START & SI
 
 while(!(I2C0CONSET & (1<<3)));      //-- End CTRL
 
 return 0;
}

//---------------------------------------------------------------------------
static void i2c_lpc_wr_byte(int byte)
{
   I2C0DAT = byte;
   I2C0CONCLR = (1<<3);                //-- Clear SI
   while(!(I2C0CONSET & (1<<3)));      //-- End wr POINT
}

//---------------------------------------------------------------------------
static void i2c_lpc_stop()
{
    //-- Set STOP condition
   I2C0CONCLR = (1<<3);                  //-- Clear SI
   I2C0CONSET |=  (1<<2) | (1<<4); //-- Clear NO ASK
}




//----------------------------------------------------------------------------
static int write_eeprom(unsigned char add, unsigned char  dat)            //-- Bytes to write qty
{
    unsigned char rc;
	//--- wr START + CONTROL
   rc=i2c_lpc_ctrl(0x98); //-- Now WR (RD/WI = 0)
   
   //--- wr ADDRESS
   i2c_lpc_wr_byte(add);
   
   //---  Write  data
    i2c_lpc_wr_byte(dat);

	delay(1000);
   //-----------------------
   i2c_lpc_stop();

   //i2c_lpc_ask_polling_op(0xa0);    //-- wait until write finished
   i2c_delay(100);
   i2c_lpc_stop();
   return 0;
}


//----------------------------------------------------------------------------
unsigned char read_eeprom(unsigned char add)            //-- Bytes to read qty
{
 unsigned char val;
 i2c_lpc_ctrl(0x98); //-- Now WR (RD/WI = 0)
 i2c_lpc_wr_byte(add);
 i2c_lpc_ctrl(0x99); //-- Now RD (RD/WI = 1)
      
 I2C0CONCLR = (1<<3);
 I2C0CONSET |= (1<<2);
      
 while(!(I2C0CONSET & (1<<3)));  //-- End Data from slave;
 val = (unsigned char)I2C0DAT;
      
 i2c_lpc_stop();     //---- Set STOP ---
 return(val);
}

char mems_start(void)
{
	memsdata=read_eeprom(3)&0x3f;

	return (memsdata);
}

void mems_init(void)
{
	i2c_lpc_init(1);		// Initialize I2C
  	i2c_delay(1000);
  	i2c_delay(1000);

	write_eeprom(7,0x00);
    delay(500);
    write_eeprom(7,0x01);
    delay(500);
    write_eeprom(8,0x3F);
    delay(500);
}

void mems_stop(void)
{
	write_eeprom(7,0x00);
    delay(200);

  	write_eeprom(7,0x01);
    delay(200);
}
