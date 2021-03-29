/**
 * @file LCD_Control.cpp
 * @author Vincent de Man
 * @brief 
 * @version 0.1
 * @date 2021-03-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "LCD_Control.h"
#include <driver/gpio.h>

LCD_Control::LCD_Control(gpio_num_t _RS, gpio_num_t _E, gpio_num_t _D0, gpio_num_t _D1, gpio_num_t _D2, gpio_num_t _D3, gpio_num_t _D4, gpio_num_t _D5, gpio_num_t _D6, gpio_num_t _D7)
{
    LCD_RS = _RS;
    LCD_E  = _E;
    LCD_D0 = _D0;
    LCD_D1 = _D1;
    LCD_D2 = _D2;
    LCD_D3 = _D3;
    LCD_D4 = _D4;
    LCD_D5 = _D5;
    LCD_D6 = _D6;
    LCD_D7 = _D7;

}