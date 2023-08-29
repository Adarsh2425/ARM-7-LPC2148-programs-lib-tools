// Define LCD PinIO Mask 
#define  LCD_RS     0x00010000   						// P1.16(0000 0000 0000 000x 0000 0000 0000 0000)
#define  LCD_EN     0x00020000   						// P1.17(0000 0000 0000 00x0 0000 0000 0000 0000)

#define  LCD_D4     0x00040000   						// P1.18(0000 0000 0000 0x00 0000 0000 0000 0000)
#define  LCD_D5     0x00080000   						// P1.19(0000 0000 0000 x000 0000 0000 0000 0000)
#define  LCD_D6     0x00100000   						// P1.20(0000 0000 000x 0000 0000 0000 0000 0000)
#define  LCD_D7     0x00200000   						// P1.21(0000 0000 00x0 0000 0000 0000 0000 0000)

/////////////////////////////  Delay Function //////////////////////////
void main_delay( unsigned int value )
{
 unsigned int ui_temp1,ui_temp2;	 // Delay Variables 
 for(ui_temp1=0;ui_temp1<value;ui_temp1++)	//Delay loop
 for(ui_temp2=0;ui_temp2<5000;ui_temp2++);	//Delay loop
}

///////////////////////  LCD Command Sending Function/////////////////////
void lcd_cmd(unsigned char val)
{
 unsigned int lcd_ch;			   // LCD Initial Data 
 unsigned int lcd_i;			   // LCD Initial Delay Count 

 IOCLR1 = LCD_RS ;					// RS = 0 
 
 lcd_ch=((val>>4)&0x0F);			// Strobe 4-Bit High-Nibble to LCD

 IOCLR1 = (LCD_D7|LCD_D6|LCD_D5|LCD_D4);	 // Reset 4-Bit Pin Data
 IOSET1 = (lcd_ch<<18); 			    	// Data Send to Respective Pins    
 IOSET1 = LCD_EN ;					// EN = 1 (Enable)
 for (lcd_i=0;lcd_i<10000;lcd_i++);	//delay
 IOCLR1 = LCD_EN ;					// EN = 0 (Disable)	
  
 lcd_ch=(val&0x0F);				  		// Strobe 4-Bit Low-Nibble to LCD

 IOCLR1 = (LCD_D7|LCD_D6|LCD_D5|LCD_D4); // Reset 4-Bit Pin Data
 IOSET1 = (lcd_ch<<18); 				// EN,0,RW,RS:DDDD:0000:0000:0000:0000:0000:0000   
 IOSET1 = LCD_EN ;					// EN = 1 (Enable)
 for (lcd_i=0;lcd_i<10000;lcd_i++);	//delay
 IOCLR1 = LCD_EN ;					// EN = 0 (Disable)	
  
 for (lcd_i=0;lcd_i<10000;lcd_i++);	 //delay
}

///////////////////////LCD Single Charecter Display Function/////////////////////////////////////////
void lcd_data(unsigned char val)
{
 unsigned int lcd_ch;		   // LCD Initial Data 
 unsigned int lcd_i;		   // LCD Initial Delay Count 

 IOSET1 = LCD_RS ;	 		// RS = 1 
 
 lcd_ch=((val>>4)&0x0F);	// Strobe 4-Bit High-Nibble to LCD

 IOCLR1 = (LCD_D7|LCD_D6|LCD_D5|LCD_D4); // Reset 4-Bit Pin Data
 IOSET1 = (lcd_ch<<18); 				 // Data Send to Respective Pins  
 IOSET1 = LCD_EN ;					// EN = 1 (Enable)
 for (lcd_i=0;lcd_i<10000;lcd_i++);	// delay
 IOCLR1 = LCD_EN ;					// EN = 0 (Disable)	
  
 lcd_ch=(val&0x0F);				  	// Strobe 4-Bit Low-Nibble to LCD

 IOCLR1 = (LCD_D7|LCD_D6|LCD_D5|LCD_D4); // Reset 4-Bit Pin Data
 IOSET1 = (lcd_ch<<18); 				 // Data Send to Respective Pins   
 
 IOSET1 = LCD_EN ;					// EN = 1 (Enable)
 for (lcd_i=0;lcd_i<10000;lcd_i++);	//delay
 IOCLR1 = LCD_EN ;					// EN = 0 (Disable)	
  
 for (lcd_i=0;lcd_i<10000;lcd_i++);	 //delay
}


///////////////////// LCD String Display Function ///////////////////
void lcd_string(unsigned char* str)
{
 while(*str)				   // Cheack Data is there or not
 lcd_data(*str++);			  //LCD Single Charecter Display Function
}

/////////////////  LCD Initialization Function   ////////////////////
void lcd_init()
{
 unsigned int lcd_main_i;			// LCD Initial Delay Count 

 PINSEL2 |= 0x00000000;				// GPIO1[31..16] = I/O Function
 IODIR1  |= 0x003F0000 ;		    // GPIO1[21..16] = OUT Direction
 					
 for (lcd_main_i=0;lcd_main_i<10000;lcd_main_i++);		    // Power-On Delay (15 mS)

 IOCLR1 = ((LCD_D7|LCD_D6|LCD_D5|LCD_D4|LCD_RS|LCD_EN));	// Reset (RS,EN,4-Bit Data) Pin
 IOSET1 = (LCD_D5|LCD_D4);			// Set D4,D5
 IOSET1 = LCD_EN ;					// EN = 1 (Enable)
 for (lcd_main_i=0;lcd_main_i<10000;lcd_main_i++);			// Delay 
 IOCLR1 = LCD_EN ;					// EN = 0 (Disable)	
 for (lcd_main_i=0;lcd_main_i<10000;lcd_main_i++);	        // Delay 


 IOCLR1 = ((LCD_D7|LCD_D6|LCD_D5|LCD_D4|LCD_RS|LCD_EN));	// Reset (RS,EN,4-Bit Data) Pin
 IOSET1 = (LCD_D5|LCD_D4);			// Set D4,D5					
 IOSET1 = LCD_EN ;					// EN = 1 (Enable)
 for (lcd_main_i=0;lcd_main_i<10000;lcd_main_i++);			// Delay 
 IOCLR1 = LCD_EN ;					// EN = 0 (Disable)	
 for (lcd_main_i=0;lcd_main_i<10000;lcd_main_i++);	        // delay 
  
 IOCLR1 = ((LCD_D7|LCD_D6|LCD_D5|LCD_D4|LCD_RS|LCD_EN));	// Reset (RS,RW,EN,4-Bit Data) Pin
 IOSET1 = (LCD_D5|LCD_D4);			// Set D4,D5 
 IOSET1 = LCD_EN ;					// EN = 1 (Enable)
 for (lcd_main_i=0;lcd_main_i<10000;lcd_main_i++);		    // Delay 
 IOCLR1 = LCD_EN ;					// EN = 0 (Disable)	
 for (lcd_main_i=0;lcd_main_i<10000;lcd_main_i++);		    // Delay 			  
 
 IOCLR1 = ((LCD_D7|LCD_D6|LCD_D5|LCD_D4|LCD_RS|LCD_EN));	// Reset (RS,RW,EN,4-Bit Data) Pin
 IOSET1 = (LCD_D5);					// Set D4,D5 
 IOSET1 = LCD_EN ;					// EN = 1 (Enable)
 for (lcd_main_i=0;lcd_main_i<10000;lcd_main_i++);			// Delay 
 IOCLR1 = LCD_EN ;					// EN = 0 (Disable)	
 for (lcd_main_i=0;lcd_main_i<10000;lcd_main_i++);		    // Delay 
 			
 lcd_cmd(0x28);    // LCD 4-Bit Mode
 lcd_cmd(0x0c);    // LCD Courser Blinking Stop
 lcd_cmd(0x06);    // LCD Shift Display Right
 lcd_cmd(0x01);	   // LCD Clear Display
 for (lcd_main_i=0;lcd_main_i<10000;lcd_main_i++);		// Wait Command Ready		
}

void lcd_num(unsigned int lcd_value)
{
 unsigned int lcd_arr[10],lcd_val;
 
 for(lcd_val=1;lcd_val<5;lcd_val++)
 {
  lcd_arr[lcd_val] = lcd_value%10;
  lcd_value  = lcd_value/10;
 }
 
 for(lcd_val=4; lcd_val!=0 ; lcd_val--)					//sending data to LCD
 {
  lcd_data(lcd_arr[lcd_val]+48);
 }
}
