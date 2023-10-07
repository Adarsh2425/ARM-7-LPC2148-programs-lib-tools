/**
 * @file delay.c
 * @author Kiran Lavu (kiranlavu9@gmail.com)
 * @brief Function definitions for delay APIs
 * @version 0.1
 * @date 2022-09-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "delay.h"

void delay(unsigned int a)
{
    unsigned int i,j;
    for(i = 0; i < a; i++)
    for(j = 0; j < 6000; j++);
}
