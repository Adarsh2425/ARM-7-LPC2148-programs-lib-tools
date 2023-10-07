/**
 * @file KeyPad.h
 * @author Kiran Lavu (kiranlavu9@gmail.com)
 * @brief APIs for hex keypad
 * @version 0.1
 * @date 2022-09-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __KEYPAD_H__
#define __KEYPAD_H__

#include "PinPositions.h"

#define COLUMNS (COL1 | COL2 | COL3 | COL4)
#define ROWS (ROW1 | ROW2 | ROW3 | ROW4)

/**
 * @brief Set up keypad
 * 
 * Here, we are configuring kepy pad to have rows as input and columns as output.
 * 
 */
void keyPad_init(void);

/**
 * @brief Function to get the button pressed
 * 
 * @return ASCII char for pressed button. 
 */
unsigned char keyPad_GetKeyPressed(void);

#endif
