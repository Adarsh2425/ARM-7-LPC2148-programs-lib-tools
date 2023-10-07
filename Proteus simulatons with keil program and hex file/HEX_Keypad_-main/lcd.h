/**
 * @file lcd.h
 * @author Kiran Lavu (kiranlavu9@gmail.com)
 * @brief This file contains APIs for LCD module
 * @version 0.1
 * @date 2022-09-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __LCD_H__
#define __LCD_H__

#include "PinPositions.h"

/**
 * @brief Initializes the LCD.
 * 
 * The LCD module will be setup as follows
 * 
 * Mode: 8 bit, 2 line
 * Display: On, Cursor Off, Blink off
 * Clears LCD and set the cursor at first row, first column.
 * This also sets the RW pin to LOW.
 */
void lcd_init(void);

/**
 * @brief Function to display a character on LCD at current cursor position
 * 
 * @param[in] ch - character to be displayed on LCD - Must be an ASCII character
 */
void lcd_data(unsigned char d);

/**
 * @brief Writes a string to LCD. 
 * 
 * This function will write the string pointed by pString starting at current position of cursor
 * 
 * @param[in] pString - Pointer to string which is to be written to LCD
 */
void lcd_str(unsigned char *pString);

/**
 * @brief Writes a number to LCD from current position
 * 
 * @param[in] num - Unsigend integer to be displayed on the screen.
 */
void lcd_num(unsigned int num);

/**
 * @brief Function to send commands to LCD
 * 
 * @param[in] cmd - Command to be written to LCD
 */
void lcd_cmd(unsigned char cmd);

#endif
