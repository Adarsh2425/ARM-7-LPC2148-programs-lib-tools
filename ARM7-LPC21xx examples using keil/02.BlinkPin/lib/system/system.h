#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "LPC214x.H"
#include "irq.h"
#include "delay.h"
#include "gpio.h"
#include "target.h"

#include <stdint.h>
#include <stdio.h>

#define byte uint8_t

#ifndef NULL
#define NULL    ((void *)0)
#endif

#define FAIL	( 9 )
#define SUCCESS	( 10 )

#define TRUE	( 1 )
#define FALSE	( 0 )

#define true	( 0 )
#define false	( 1 )

#endif
