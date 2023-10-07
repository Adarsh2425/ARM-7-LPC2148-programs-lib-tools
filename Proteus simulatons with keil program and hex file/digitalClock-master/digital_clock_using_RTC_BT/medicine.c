#include<lpc213x.h>
#include<stdio.h>

#include "LCD Header.h"
#include "edit header.h"
#include "UART Header.h"

#define fpclk 15000000
#define MASKSEC 0x3F
#define MASKMIN 0x3F00
#define MASKHOUR 0xF0000

// KEYPAD Interrupt Service Routine
void ISR_KEYPAD(void) __irq
{
 edit_function();
 EXTINT = 0x04;
 VICVectAddr = 0x00;
}

// RTC Interrupt Service Routine
void ISR_RTC(void) __irq
{
 char str[20];
 if(ILR & 0x01)
 {
     sec = CTIME0 & MASKSEC;
	 min = (CTIME0 & MASKMIN) >> 8;
	 hour = (CTIME0 & MASKHOUR) >> 16;
	 ILR = 0x01;
	 LCD_CMD(0x85);
	 sprintf(str,"%d: %d: %d",hour,min,sec);
	 LCD_INIT();
	 LCD_STRING(str);
	 
 }
 else if(ILR & 0x02)
 {
     LCD_INIT();
	 LCD_STRING("Medicine Alarm");
	 UART0_Init();
	 UART0_Send_String("Medicine Alarm");
	 ILR = 0x02;    
 }
 VICVectAddr = 0;
}

// RTC INITIALIZATION
void RTC_Init()
{
	 ILR = 0x01;
	 CCR = 0x02;
	 CIIR = 0x07;
	 PREINT = (int)(fpclk/32768)-1;
	 PREFRAC = (int)(fpclk-((PREINT+1)*32768));
	 SEC = 5;
	 MIN = 9;
	 HOUR = 11;
	 ALSEC = 11;
	 ALMIN = 9;
	 ALHOUR =  11;
	 CCR = 0x01;
	 VICIntSelect &= (~(1<<13));
	 VICVectCntl1 = 0x20 | 13;
	 VICVectAddr1 = (long)ISR_RTC;
	 VICIntEnable |= (1<<13);
}

// KEYPAD INTERRUPT INITIALIZATION
void keypad_interrupt_init()
{
	 PINSEL0 &=(~((1<<15)|(1<<14))); // P0.7
	 PINSEL0 |=(0x3)<<14;
	 EXTINT = 0x04;
	 EXTMODE = 0x04;
	 EXTPOLAR = 0x00;
	 VICIntSelect &= (~(1<<16));
	 VICVectCntl0 = 0x20 | 16; 
	 VICVectAddr0 = (long)ISR_KEYPAD;
	 VICIntEnable |= (1<<16); 
}

int main()
{
     PINSEL2 = 0x00000000;
	 LCD_INIT();
	 LCD_CMD(0x80);
	 LCD_STRING("Time:");
	 LCD_CMD(0xC0);
	 LCD_STRING("Press EDIT");
	 RTC_Init();
	 keypad_interrupt_init();
	 while(1)
	 {
	     
	 }
	 return 0;
}
