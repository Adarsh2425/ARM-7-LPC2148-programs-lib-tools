#include<lpc213x.h>
#include <string.h>
#include <stdlib.h>
#include "Keypad Header.h"

unsigned char key_val;
char hr[2], mi[2], se[2];
char alhr[2], almi[2], alse[2];
int sec, min, hour, j;
int flag=0;
//int alsec,almin,alhour;

int int_conversion(char* str)
{
	 int c, p=0;
     for (c = 1; c >= 0; c--) 
	 {
        p = p * 10 + str[c] - '0';
     }
     return p;
}

int edit_function()
{
 strcpy(hr, "");
 strcpy(mi, "");
 strcpy(se, "");
 strcpy(alhr, "");
 strcpy(almi, "");
 strcpy(alse, "");
 LCD_INIT();
 LCD_STRING("Edit 1. Time");
 LCD_CMD(0xC0);
 LCD_STRING("2. Alarm 3.Exit");
 key_val = key_detect();
 LCD_INIT();
 LCD_DATA(key_val);
 if (key_val == '1')
 {
	  LCD_INIT();
	  LCD_STRING("Enter Hour : ");
	  LCD_CMD(0xC0);
	  for(j=0;j<2;j++)
	  {
		   hr[j]=key_detect();
		   LCD_DATA(hr[j]);
		   //delay_ms(50);
		   flag++;
		   if(flag==2)
		   {
		     flag = 0;
			 break;
		   }
	  }
	  HOUR = atoi(hr);
	  
	  LCD_INIT();
	  LCD_STRING("Enter Minute: ");
	  LCD_CMD(0xC0);
	  for(j=0;j<2;j++)
	  {
		   mi[j]=key_detect();
		   LCD_DATA(mi[j]);
		   //delay_ms(50);
		   flag++;
		   if(flag==2)
		   {
		     flag = 0;
			 break;
		   }
	  }
	  MIN = atoi(mi);
	  
	  
	  LCD_INIT();
	  LCD_STRING("Enter Second: ");
	  LCD_CMD(0xC0);
	  for(j=0;j<2;j++)
	  {
		   se[j]=key_detect();
		   LCD_DATA(se[j]);
		   //delay_ms(50);
		   flag++;
		   if(flag==2)
		   {
		     flag = 0;
			 break;
		   }
	  }
	  SEC = atoi(se);
  
 }
 else if(key_val == '2')
 {
	  LCD_INIT();
	  LCD_STRING("Alarm Hour : ");
	  LCD_CMD(0xC0);
	  for(j=0;j<2;j++)
	  {
		   alhr[j]=key_detect();
		   LCD_DATA(alhr[j]);
		   //delay_ms(50);
		   flag++;
		   if(flag==2)
		   {
		     flag = 0;
			 break;
		   }
	  }
	  ALHOUR = atoi(alhr);
	  
	  
	  LCD_INIT();
	  LCD_STRING("Alarm Minute: ");
	  LCD_CMD(0xC0);
	  for(j=0;j<2;j++)
	  {
		   almi[j]=key_detect();
		   LCD_DATA(almi[j]);
		   //delay_ms(50);
		   flag++;
		   if(flag==2)
		   {
		     flag = 0;
			 break;
		   }
	  }
	  ALMIN = atoi(almi);
	  
	  
	  LCD_INIT();
	  LCD_STRING("Alarm Second: ");
	  LCD_CMD(0xC0);
	  for(j=0;j<2;j++)
	  {
		   alse[j]=key_detect();
		   LCD_DATA(alse[j]);
		   //delay_ms(50);
		   flag++;
		   if(flag==2)
		   {
		     flag = 0;
		     break;
		   }
	  }
	  ALSEC = atoi(alse);
  }
  else if(key_val == '3')
  {
      LCD_INIT();
	  LCD_STRING("Exit Editing");
	  return 0;
  }
  return 1;
}

