#include <lpc214x.h>
#include "gpio.h"
#include "timer0.h"

//pin 0.6 ->led

int main()
{
	pinSelect(6,0);
	pinWrite(6,1);
	delay_milliseconds(10);
	pinWrite(6,0);
}