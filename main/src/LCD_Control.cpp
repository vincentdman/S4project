/**
 * @file LCD_Control.cpp
 * @author Vincent de Man
 * @brief Source file for LCD_Control class.
 * @version 1.1
 * @date 2021-03-29
 * @class LCD_Control class to use a lcd display easily 
 * @copyright Copyright (cpp) 2021
 * @details Implementation of the LCD_Control class. It uses the intherited handle gpio functions.
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

    LCD_Control::LCD_Control(LCD_Pinout_t &LCD_Pinout_Configuration)
        : LCD_RS(LCD_Pinout_Configuration._RS), LCD_E(LCD_Pinout_Configuration._E), LCD_D0(LCD_Pinout_Configuration._D0), LCD_D1(LCD_Pinout_Configuration._D1),
          LCD_D2(LCD_Pinout_Configuration._D2), LCD_D3(LCD_Pinout_Configuration._D3), LCD_D4(LCD_Pinout_Configuration._D4), LCD_D5(LCD_Pinout_Configuration._D5),
          LCD_D6(LCD_Pinout_Configuration._D6), LCD_D7(LCD_Pinout_Configuration._D7), BitMode(LCD_Pinout_Configuration._BitMode)
    {
        LCD_Initialize();
    }

    /**
     * @brief function to write a char to the lcd.
     * 
     * @param data The char that will be written to the lcd
     * 
     * @details LCD_Write_Char function cast the input data to a std string as binary. It than uses the LCD_Write function to display the character.
     */
    void LCD_Control::LCD_Write_Char(char data)
    {
        std::string binary = std::bitset<8>(data).to_string();
        LCD_Write(binary, WriteAction);
    }

    /**
     * @brief function to write the lcd commands to the lcd
     * 
     * @param Command The command that will be written
     * 
     * @details The input is a int that gets casted to a std binary string. It then gets written to the lcd by the lcd_Write function
     */
    void LCD_Control::LCD_Write_Command(int Command)
    {
        std::string ToBin = std::bitset<8>(Command).to_string();
        LCD_Write(ToBin, RegisterSet);
    }

    /**
     * @brief Function to write a whole string to the lcd.
     * 
     * @param Data_String_ The string that will be written to the lcd.
     * 
     * @details The lcd write function takes in a std string and then uses the function LCD_Write_Char to write the string on the lcd.
     */
    void LCD_Control::LCD_Write_String(std::string Data_String_)
    {
        for (int i = 0; i < Data_String_.size(); i++)
        {
            LCD_Write_Char(Data_String_[i]);
        }
    }

    /**
     * @brief Function to initialize the lcd for use
     * 
     * @details Initializes the lcd pins to pulldown and output. The LCD_E pin gets set to low output. First there is a 50ms delay as it is needed to warm up the lcd after boot.  
     */
    void LCD_Control::LCD_Initialize()
    {
        vTaskDelay(50 / portTICK_PERIOD_MS);

        InitializeGPIO(LCD_E);
        SetLow(LCD_E);

        InitializeGPIO(LCD_RS);
        InitializeGPIO(LCD_D7);
        InitializeGPIO(LCD_D6);
        InitializeGPIO(LCD_D5);
        InitializeGPIO(LCD_D4);
        InitializeGPIO(LCD_D3);
        InitializeGPIO(LCD_D2);
        InitializeGPIO(LCD_D1);
        InitializeGPIO(LCD_D0);
    }

    void LCD_Control::LCD_Write(std::string BinaryString, int RS)
    {
        if (BitMode == FourBitMode)
        {
            LCD_WriteFourBitMode(BinaryString, RS);
        }
        else
        {
            LCD_WriteEightBitMode(BinaryString, RS);
        }
    }

    void LCD_Control::LCD_WriteFourBitMode(std::string BinaryString, int RS)
    {
        LCD_InitializeForSendingData(RS);
        LCD_SetDataFourBitModeFirstHalf(BinaryString);
        LCD_CycleDataTrough();
        LCD_SetDataFourBitModeSecondHalf(BinaryString);
        LCD_CycleDataTrough();
    }

    void LCD_Control::LCD_WriteEightBitMode(std::string BinaryString, int RS)
    {
        LCD_InitializeForSendingData(RS);
        LCD_SetDataEightBitMode(BinaryString);
        LCD_CycleDataTrough();
    }

    void LCD_Control::LCD_InitializeForSendingData(int RS)
    {
        ets_delay_us(1000);
        gpio_set_level(LCD_RS, RS);
        ets_delay_us(270);
        SetHigh(LCD_E);
        ets_delay_us(240);
    }

    void LCD_Control::LCD_CycleDataTrough(void)
    {
        ets_delay_us(300);
        SetLow(LCD_E);
        ets_delay_us(1000);
    }

    void LCD_Control::LCD_SetDataEightBitMode(std::string BinaryString)
    {
        gpio_set_level(LCD_D0, BinaryString[7] - '0');
        gpio_set_level(LCD_D1, BinaryString[6] - '0');
        gpio_set_level(LCD_D2, BinaryString[5] - '0');
        gpio_set_level(LCD_D3, BinaryString[4] - '0');
        gpio_set_level(LCD_D4, BinaryString[3] - '0');
        gpio_set_level(LCD_D5, BinaryString[2] - '0');
        gpio_set_level(LCD_D6, BinaryString[1] - '0');
        gpio_set_level(LCD_D7, BinaryString[0] - '0');
    }

    void LCD_Control::LCD_SetDataFourBitModeFirstHalf(std::string BinaryString)
    {
        gpio_set_level(LCD_D4, BinaryString[3] - '0');
        gpio_set_level(LCD_D5, BinaryString[2] - '0');
        gpio_set_level(LCD_D6, BinaryString[1] - '0');
        gpio_set_level(LCD_D7, BinaryString[0] - '0');
    }

    void LCD_Control::LCD_SetDataFourBitModeSecondHalf(std::string BinaryString)
    {
        SetHigh(LCD_E);
        ets_delay_us(240);
        gpio_set_level(LCD_D4, BinaryString[7] - '0');
        gpio_set_level(LCD_D5, BinaryString[6] - '0');
        gpio_set_level(LCD_D6, BinaryString[5] - '0');
        gpio_set_level(LCD_D7, BinaryString[4] - '0');
    }
}