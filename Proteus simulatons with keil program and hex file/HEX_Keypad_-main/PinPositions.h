/**
 * @file PinPositions.h
 * @author Kiran Lavu (kiranlavu9@gmail.com)
 * @brief This file contains all the pin positions for hardware connected to microcontroller
 * @version 0.1
 * @date 2022-09-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __PINPOSITIONS_H__
#define __PINPOSITIONS_H__

// Pin positions for LCD
#define RS 10
#define RW 12
#define EN 13
#define DATA 15

/****************Port 0 pins****************/
// Pin position for buzzer
#define BUZZER_PIN 11

// Pin Posiitons for ADC Potentiometer
#define POT_PIN 28

// Pin position for Temperature sensor
#define TEMP_SENSOR 29

/****************Port 1 pins****************/
// Pin positions for LEDs
#define LED1 1 << 17
#define LED2 1 << 18
#define LED3 1 << 19
#define LED4 1 << 20
#define LED5 1 << 21
#define LED6 1 << 22
#define LED7 1 << 23
#define LED8 1 << 24

//Pin positions for Keypad
#define ROW1 1 << 21
#define ROW2 1 << 22
#define ROW3 1 << 23
#define ROW4 1 << 24
#define COL1 1 << 17
#define COL2 1 << 18
#define COL3 1 << 19
#define COL4 1 << 20

#endif
