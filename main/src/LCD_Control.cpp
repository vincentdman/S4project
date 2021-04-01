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
    FourBitMode = 1; 
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
    FourBitMode = 0;
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
    LCD_Write(binary);
}

void LCD_Control::LCD_Write_Command(int Command)
{
    std::string ToBin = std::bitset<8>(Command).to_string();
    LCD_Write(ToBin);
}
void LCD_Control::LCD_Write_String(std::string Data_String_){
    for(char& k : Data_String_)
    {
        LCD_Write_Char(Data_String_[k]);
    }
}

void LCD_Control::LCD_Write(std::string BinaryString)
{
    switch (FourBitMode)
    {
    case 0:
       SetHigh(LCD_RS);
       SetHigh(LCD_E);
            gpio_set_level(LCD_D4, BinaryString[0]);
             gpio_set_level(LCD_D5, BinaryString[1]);
              gpio_set_level(LCD_D6, BinaryString[2]);
               gpio_set_level(LCD_D7, BinaryString[3]);
       vTaskDelay(10/portTICK_PERIOD_MS);
       SetLow(LCD_E);
       vTaskDelay(100/portTICK_PERIOD_MS);
       SetHigh(LCD_E);
       SetHigh(LCD_RS);
            gpio_set_level(LCD_D4, BinaryString[4]);
             gpio_set_level(LCD_D5, BinaryString[5]);
              gpio_set_level(LCD_D6, BinaryString[6]);
               gpio_set_level(LCD_D7, BinaryString[7]);
    vTaskDelay(10/portTICK_PERIOD_MS);
       SetLow(LCD_E);
       SetLow(LCD_RS);
       vTaskDelay(100/portTICK_PERIOD_MS);
        break;

    case 1:
       SetHigh(LCD_RS);
       SetHigh(LCD_E);
        gpio_set_level(LCD_D0, BinaryString[0]);
         gpio_set_level(LCD_D1, BinaryString[1]);
          gpio_set_level(LCD_D2, BinaryString[1]);
           gpio_set_level(LCD_D3, BinaryString[3]);
            gpio_set_level(LCD_D4, BinaryString[4]);
             gpio_set_level(LCD_D5, BinaryString[5]);
              gpio_set_level(LCD_D6, BinaryString[6]);
               gpio_set_level(LCD_D7, BinaryString[7]);
       vTaskDelay(10/portTICK_PERIOD_MS);
       SetLow(LCD_E);
       SetLow(LCD_RS);
       vTaskDelay(100/portTICK_PERIOD_MS);
        break;
    default:
        break;
    }
}

}