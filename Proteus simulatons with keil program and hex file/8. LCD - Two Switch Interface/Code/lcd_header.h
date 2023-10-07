void lcd_init();                //LCD initialization function
void lcd_data(unsigned char);   //Function to send DATA into the LCD
void lcd_cmd(unsigned char);    //Function to send COMMAND into the LCD
void lcd_dis(unsigned char *);  //LCD string display function
void delay();                   //Function to generate a delay