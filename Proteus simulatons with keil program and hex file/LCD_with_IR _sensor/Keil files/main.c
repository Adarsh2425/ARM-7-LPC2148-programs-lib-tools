#include <lpc214x.h>

#define bit(x) (1<<x)
#define delay for(i=0;i<10500;i++);

unsigned int i;

void lcd_int();
void dat(unsigned char);
void cmd(unsigned char);
void string(unsigned char *);

void main()
{
    IO0DIR|=0XFFF; //makes all the pins form 0 to 11 as output 
		//our IR sensor will be connected to 14th pin and IO0DIR will have alredy initialized all the other pins as input other than 0 to 11	
	
    lcd_int();
    cmd(0x80); //0x8a initially //0x80 - from the start
		
	
    while(1) 
		{
      //shift the entire display to left
			
			if((IOPIN0 & 0x00004000) == 0x00004000) //to read value of out pin of the IR sensor
				string("Objt detected!!!");
			else 
				string("Objt not detected");
			
			cmd(0x01); //- clear display screen
        delay;
    }
}

void lcd_int() //LCD Commands 
{
    cmd(0x38); //0011 0000 - initilaizing the 2 lines 5x7 matrix in the LCD
    cmd(0x0c); //0000 1100 - display on cursor off
    cmd(0x06); //0000 0110 - increment cursor (shift to right)
    cmd(0x01); //0000 0001 - clear display screen
    cmd(0x80); //1000 0000 - Force cursor to begenning of 1st line
}

void cmd(unsigned char a)
{
    IO0PIN &= 0x00;    //to read the status of the pin, but here we are just resting the IO0PIN
    IO0PIN |= (a<<0);  //updated 0011 0000 for 0x30 since a<<0 will not left shift.
    IO0CLR |= bit(8);  //rs=0 //8 is in decimal, 8 is shifted //#define bit(8) (1<<8)
    IO0CLR |= bit(9);  //rw=0 
    IO0SET |= bit(10); //en=1 when we set and reset the values on this bit, 
											 //i.e Enable pin of the LCD that is connected to the LPC2148, the data(here its the initial commands) is sent only when high to low signal is being formed
    delay; 
	
    IO0CLR |= bit(10);  //en=0
}

void dat(unsigned char b)
{
    IO0PIN &= 0x00;                  //clearing 
    IO0PIN |= (b<<0); 
    IO0SET |= bit(8);                //rs=1
    IO0CLR |= bit(9);                //rw=0
    IO0SET |= bit(10);               //en=1
	
    delay;
	
    IO0CLR |= bit(10);               //en=0
}

void string(unsigned char *p) //to output the strings to the LCD character by character
{
    while(*p != '\0') 
		{
        dat(*p++);
    }
}