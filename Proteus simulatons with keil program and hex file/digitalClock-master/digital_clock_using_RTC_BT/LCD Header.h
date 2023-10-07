#include<lpc213x.h>
#include<stdio.h>
#define LCD	(0x0F<<20)
#define RS	(1<<17)
#define RW	(1<<18)
#define EN	(1<<19)

#define RS_High()  IOSET1 = RS
#define RS_Low()   IOCLR1 = RS
#define RW_High()  IOSET1 = RW
#define RW_Low()   IOCLR1 = RW
#define EN_High()  IOSET1 = EN
#define EN_Low()   IOCLR1 = EN			 

int i;

void delay_ms(unsigned int t)
{
 //unsigned int t;
 while(t--)
 {
  for(i=0;i<10000;i++);
 }
}

void LCD_CMD(unsigned char ch)
{
 char temp;
 temp = (ch & 0xF0) >> 4;
 IOCLR1 = LCD;
 IOSET1 = (temp<<20);
 RS_Low();
 RW_Low();
 EN_High();
 delay_ms(3);
 EN_Low();
 temp = (ch & 0x0F);
 IOCLR1 = LCD;
 IOSET1 = (temp<<20);
 EN_High();
 delay_ms(3);
 EN_Low();
}

void LCD_DATA(unsigned char ch)
{
  char temp;
  temp=(ch&0xF0)>>4;
  IOCLR1 = LCD;
  IOSET1 = (temp<<20);
  RS_High();
  RW_Low();
  EN_High();
  delay_ms(3);
  EN_Low();
  temp=(ch&0x0F);
  IOCLR1 = LCD;
  IOSET1 = (temp<<20);
  EN_High();
  delay_ms(3);
  EN_Low();
}

void LCD_INIT()
{
  IODIR1 |= LCD | RS | RW | EN;
  LCD_CMD(0x02);
  LCD_CMD(0x28);
  LCD_CMD(0x06);
  LCD_CMD(0x0C);
  LCD_CMD(0x01);
  //LCD_CMD(0x);
}

void LCD_STRING(char *str)
{
 while(*str)
 {
  LCD_DATA(*str++);
 }
}

void LCD_PRINT_NUM(int n)
{
  char str[6];
  sprintf(str,"%d",n);
  LCD_STRING(str);
}

