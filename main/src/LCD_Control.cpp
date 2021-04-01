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
#include <string>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "LCD_Commands.h"
#include <bitset>

extern "C"{
LCD_Control::LCD_Control(gpio_num_t _RS, gpio_num_t _E, gpio_num_t _D0, gpio_num_t _D1, gpio_num_t _D2, gpio_num_t _D3, gpio_num_t _D4, gpio_num_t _D5, gpio_num_t _D6, gpio_num_t _D7)
{
    FourBitMode = false; 
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
LCD_Control::LCD_Control(gpio_num_t _RS, gpio_num_t _E, gpio_num_t _D4, gpio_num_t _D5 ,gpio_num_t _D6, gpio_num_t _D7)
{
    FourBitMode = true;
    LCD_RS = _RS;
    LCD_E  = _E;
    LCD_D4 = _D4;
    LCD_D5 = _D5;
    LCD_D6 = _D6;
    LCD_D7 = _D7;
}

void LCD_Control::LCD_Write_Char(char data)
{
    std::string binary = std::bitset<8>(data).to_string();
    
    switch (FourBitMode)
    {
    case true:

        break;
    case false:
       SetHigh(LCD_RS);
       SetHigh(LCD_E);
        gpio_set_level(LCD_D0, binary[0]);
         gpio_set_level(LCD_D1, binary[1]);
          gpio_set_level(LCD_D2, binary[1]);
           gpio_set_level(LCD_D3, binary[3]);
            gpio_set_level(LCD_D4, binary[4]);
             gpio_set_level(LCD_D5, binary[5]);
              gpio_set_level(LCD_D6, binary[6]);
               gpio_set_level(LCD_D7, binary[7]);
       vTaskDelay(100/portTICK_PERIOD_MS);
       SetLow(LCD_E);
       SetLow(LCD_RS);
        break;
    default:
        break;
    }

}
}