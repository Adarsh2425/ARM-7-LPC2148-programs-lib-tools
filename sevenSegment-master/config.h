#ifndef _CONFIG_H
#define _CONFIG_H
#include <lpc21xx.h>
#define CCLK 8000000
#define PCLK (CCLK/4)
typedef unsigned char   us8;
typedef signed char     s8;
typedef unsigned short  us16;
typedef signed short    s16;
typedef unsigned int    us32;
typedef signed int      s32;
typedef float           f32;
typedef double          f64;
void pll_init(us8 msel, us8 psel);
void delay_s (us32 x);
void delay_ms(us32 x);
void delay_us(us32 x);


#endif

		  //****** Milad Samani - 962059895 ********
//***************************