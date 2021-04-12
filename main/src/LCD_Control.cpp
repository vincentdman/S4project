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
#include <iostream>

extern "C"
{
    LCD_Control::LCD_Control(gpio_num_t _RS, gpio_num_t _E, gpio_num_t _D0, gpio_num_t _D1, gpio_num_t _D2, gpio_num_t _D3, gpio_num_t _D4, gpio_num_t _D5, gpio_num_t _D6, gpio_num_t _D7)
        : LCD_RS(_RS), LCD_E(_E), LCD_D0(_D0), LCD_D1(_D1), LCD_D2(_D2), LCD_D3(_D3), LCD_D4(_D4), LCD_D5(_D5), LCD_D6(_D6), LCD_D7(_D7)
    {
        BitMode = EightBitMode;
        LCD_Initialize();
    }
    LCD_Control::LCD_Control(gpio_num_t _RS, gpio_num_t _E, gpio_num_t _D4, gpio_num_t _D5, gpio_num_t _D6, gpio_num_t _D7)
        : LCD_RS(_RS), LCD_E(_E), LCD_D4(_D4), LCD_D5(_D5), LCD_D6(_D6), LCD_D7(_D7)
    {
        BitMode = FourBitMode;
        LCD_Initialize();
    }

    void LCD_Control::LCD_Write_Char(char data)
    {
        std::string binary = std::bitset<8>(data).to_string();
        LCD_Write(binary, WriteAction);
    }

    void LCD_Control::LCD_Write_Command(int Command)
    {
        std::string ToBin = std::bitset<8>(Command).to_string();
        LCD_Write(ToBin, RegisterSet);
    }
    void LCD_Control::LCD_Write_String(std::string Data_String_)
    {
        for (int i =0; i < Data_String_.size(); i++)
        {
            LCD_Write_Char(Data_String_[i]);
        }
    }

    void LCD_Control::LCD_Initialize()
    {
        InitializeGPIO(LCD_RS);
        InitializeGPIO(LCD_E);
        InitializeGPIO(LCD_D0);
        InitializeGPIO(LCD_D1);
        InitializeGPIO(LCD_D2);
        InitializeGPIO(LCD_D3);
        InitializeGPIO(LCD_D4);
        InitializeGPIO(LCD_D5);
        InitializeGPIO(LCD_D6);
        InitializeGPIO(LCD_D7);
        SetLow(LCD_E);
    }

    void LCD_Control::LCD_Write(std::string BinaryString, int RS)
    {
        switch (BitMode)
        {
        case FourBitMode:
    
            ets_delay_us(1000);
            gpio_set_level(LCD_RS,RS);
            ets_delay_us(270);
            SetHigh(LCD_E);
            ets_delay_us(240);
            gpio_set_level(LCD_D4, BinaryString[3]-'0');
            gpio_set_level(LCD_D5, BinaryString[2]-'0');
            gpio_set_level(LCD_D6, BinaryString[1]-'0');
            gpio_set_level(LCD_D7, BinaryString[0]-'0');
            ets_delay_us(300);
            SetLow(LCD_E);
            ets_delay_us(1000);

            SetHigh(LCD_E);
            ets_delay_us(240);
            gpio_set_level(LCD_D4, BinaryString[7]-'0');
            gpio_set_level(LCD_D5, BinaryString[6]-'0');
            gpio_set_level(LCD_D6, BinaryString[5]-'0');
            gpio_set_level(LCD_D7, BinaryString[4]-'0');
            ets_delay_us(300);
            SetLow(LCD_E);
            ets_delay_us(1000);
            break;

        case EightBitMode:
            ets_delay_us(1000);
            gpio_set_level(LCD_RS,RS);
            ets_delay_us(270);
            SetHigh(LCD_E);
            ets_delay_us(240);
            gpio_set_level(LCD_D0, BinaryString[7]-'0');
            gpio_set_level(LCD_D1, BinaryString[6]-'0');
            gpio_set_level(LCD_D2, BinaryString[5]-'0');
            gpio_set_level(LCD_D3, BinaryString[4]-'0');
            gpio_set_level(LCD_D4, BinaryString[3]-'0');
            gpio_set_level(LCD_D5, BinaryString[2]-'0');
            gpio_set_level(LCD_D6, BinaryString[1]-'0');
            gpio_set_level(LCD_D7, BinaryString[0]-'0');
            ets_delay_us(300);
            SetLow(LCD_E);
            ets_delay_us(1000);
        break;

        default:
            std::cout<<"Bitmode error, No bitmode selected."<<std::endl;
            break;
        }
    }
}