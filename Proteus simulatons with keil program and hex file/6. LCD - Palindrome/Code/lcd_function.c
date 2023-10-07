#include<lpc21xx.h>
#include "lcd_header.h"
#define bit(x) (1<<x)

void lcd_cmd(unsigned char a)  //Function to send COMMAND into the LCD
{
    IO0PIN&=0x00;                  
    IO0PIN|=(a<<0);
    IO0CLR|=bit(8);           //To send the COMMANDS into the LCD, Register Select has to be 0 ; rs=0
    IO0CLR|=bit(9);           //For writing into the LCD rw=0
    IO0SET|=bit(10);          //To latch the command/data sent into the LCD a high to low pulse is given; en=1
    delay();                  //Call a delay
    IO0CLR|=bit(10);          //en=0
}

void lcd_init()              //LCD initialization function
{
    lcd_cmd(0x30);           // 8-bit mode
	  lcd_cmd(0x38);           //activate two rows of LCD crystal
    lcd_cmd(0x0c);           //turn on display , turn off cusor
    lcd_cmd(0x06);           //increment cursor
    lcd_cmd(0x01);           //clear the screen
    lcd_cmd(0x80);           //set the cursor to the beginning of the first line
}

void lcd_data(unsigned char b)  //Function to send DATA into the LCD
{
    IO0PIN&=0x00;            //Pins of PORT 0 set to 0
    IO0PIN|=(b<<0);
    IO0SET|=bit(8);           //To send the DATA into the LCD, Register Select has to be 1 ; rs=1
    IO0CLR|=bit(9);           //For writing into the LCD rw=0
    IO0SET|=bit(10);          //To latch the command/data sent into the LCD a high to low pulse is given; en=1
    delay();                  //Call delay
    IO0CLR|=bit(10);          //en=0
}

void lcd_dis(unsigned char *p)  // LCD string display function
{
    while(*p!='\0')             
			{
        lcd_data(*p++);       // Pass the character into the data function using pointer
      }
}

void delay()                  //Delay function
{   
    unsigned int i;	
    for(i=0;i<20000;i++);
}

void isPalindrome(unsigned char* word)   //Palindrome check function
{
    unsigned char *ptr, *rev;
    ptr = word;
    while (*ptr != '\0') 
			{
        ++ptr;
      }
    --ptr;
 
    for (rev = word; ptr >= rev;) 
			{
        if (*ptr == *rev) 
				{
            --ptr;
            rev++;
        }
        else
            break;
       }
 
    if (rev > ptr)                   //if the word is a palindrome
		{
		  lcd_dis(word);                 //Display the word on the LCD
	    lcd_cmd(0xC0);                 //Force cursor to the second line
		  lcd_dis("PALINDROME");         //Display "PALINDROME" on LCD 
		}
    else                            //if the word is not a palindrome
		{
		  lcd_dis(word);                //Display the word on the LCD
	    lcd_cmd(0xC0);                //Force cursor to the second line
		  lcd_dis("NOT A PALINDROME");  //Display "NOT A PALINDROME" on LCD 
		}
}