/**
 * @file KeyPad.c
 * @author Kiran Lavu (kiranlavu9@gmail.com)
 * @brief Function definitons for keypad module.
 * @version 0.1
 * @date 2022-09-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <LPC214x.h>
#include "PinPositions.h"
#include "delay.h"
#include "KeyPad.h"
#include "lcd.h"

typedef enum
{
    false = 0, 
    true
}bool;

void keyPad_init(void)
{
    IO1DIR |= COLUMNS; // Set Columns as outputs.
    IO1DIR &= ~ROWS; // Set Rows as inputs.

    IO1CLR |= COLUMNS; // Clear column pins - pull them to low.
    IO1CLR |= ROWS; // Clear row pins.
}

unsigned char keyPad_GetKeyPressed()
{
	unsigned int i = 0;
    unsigned char pressedButton = '\0';
    unsigned int rowBuffer = 0;
    bool done = false; // flag to indicate if we are done reading one button.

    // Loop to iterate over each column
    // Logic is to set one column to low and read the row.
    // If any pin in row is low, the pressed button corresponds to that row and column combo.
    for(i = 0; i < 4; i++)
    {
        if(done == false)
        {
            IO1SET |= COLUMNS; // Make all columns as high
		    IO1SET |= ROWS; // Make all rows as high 
            IO1CLR |= ((COL1) << i); // Make one of the column pins as LOW
		    delay(10);

            if((IO1PIN & ROWS) != ROWS) // check if any button is pressed in current column
            {
				rowBuffer = (IO1PIN & ROWS); // Keep a copy of pressed button here

                if((rowBuffer & ROW1) == 0) // If button in row 1 is pressed, then row 1 will be low.
                {
                    // We are switching on 'i' here because it represets the column we are in for this iteration.
                    // If i = 0, then we are looking at column 1
                    // If i = 1, then we are looking at Column 2 and so on
                    switch (i)
                    {
                        case 0: // column 1, row 1
                            pressedButton = '0';
                            delay(100); // debounce delay
                            done = true;
                            break;
                        case 1: // Column 1, row 2
                            pressedButton = '1';
                            delay(100); // debounce delay
                            done = true;
                            break;
                        case 2: // column 1, row 3
                            pressedButton = '2';
                            delay(100); // debounce delay
                            done = true;
                            break;
                        case 3: // column 1, row 4
                            pressedButton = '3';
                            delay(100);
                            done = true;
                            break;
                        default:
                            break;
                    }
                }
                else if((rowBuffer & ROW2) == 0)
                {
                    switch (i)
                    {
                        case 0:
                            pressedButton = '4';
                            delay(100); // debounce delay
                            done = true;
                            break;
                        case 1:
                            pressedButton = '5';
                            delay(100); // debounce delay
                            done = true;
                            break;
                        case 2:
                            pressedButton = '6';
                            delay(100); // debounce delay
                            done = true;
                            break;
                        case 3:
                            pressedButton = '7';
                            delay(100);
                            done = true;
                            break;
                        default:
                            break;
                    }
                }
                else if((rowBuffer & ROW3) == 0)
                {
                    switch (i)
                    {
                        case 0:
                            pressedButton = '8';
                            delay(100); // debounce delay
                            done = true;
                            break;
                        case 1:
                            pressedButton = '9';
                            delay(100); // debounce delay
                            done = true;
                            break;
                        case 2:
                            pressedButton = 'A';
                            delay(100); // debounce delay
                            done = true;
                            break;
                        case 3:
                                pressedButton = 'B';
                                done = true;
                                delay(100);
                                break;
                        default:
                                break;
                    }

                }
                else if((rowBuffer & ROW4) == 0)
                {
                    switch (i)
                    {
                        case 0:
                            pressedButton = 'C';
                            delay(100); // debounce delay
                            done = true;
                            break;
                        case 1:
                            pressedButton = 'D';
                            delay(100); // debounce delay
                            done = true;
                            break;
                        case 2:
                            pressedButton = 'E';
                            delay(100); // debounce delay
                            done = true;
                            break;
                        case 3:
                            pressedButton = 'F';
                            delay(100);
                            done = true;
                            break;
                        default:
                            break;
                    }

                }
            }

        }
        else
        {
            // We are done reading atleast one key. No need to scan further.
            // Break the for loop and return the pressed button.
            break;
        }
    }
    return pressedButton;
}
