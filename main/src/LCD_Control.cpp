/**
 * @file LCD_Control.cpp
 * @author Vincent de Man
 * @brief 
 * @version 0.1
 * @date 2021-03-29
 * @class LCD_Control class to use a lcd display easily 
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
    /**
     * @brief Construct a new lcd control::lcd control object for 8 bit mode
     * 
     * @param _RS The register select pin of the lcd
     * @param _E  The enable pin of the lcd
     * @param _D0 The first data pin of the lcd
     * @param _D1 The second data pin of the lcd
     * @param _D2 The third data pin of the lcd
     * @param _D3 The fourth data pin of the lcd
     * @param _D4 The fith data pin of the lcd
     * @param _D5 The sixt data pin of the lcd
     * @param _D6 The seventh data pin of the lcd
     * @param _D7 The eight data pin of the lcd
     * 
     * @details constructor for the use of 8 bit mode lcd. The class gets initialized for eight bit mode.
     */
    LCD_Control::LCD_Control(gpio_num_t _RS, gpio_num_t _E, gpio_num_t _D0, gpio_num_t _D1, gpio_num_t _D2, gpio_num_t _D3, gpio_num_t _D4, gpio_num_t _D5, gpio_num_t _D6, gpio_num_t _D7)
        : LCD_RS(_RS), LCD_E(_E), LCD_D0(_D0), LCD_D1(_D1), LCD_D2(_D2), LCD_D3(_D3), LCD_D4(_D4), LCD_D5(_D5), LCD_D6(_D6), LCD_D7(_D7)
    {
        BitMode = EightBitMode;
        LCD_Initialize();
    }

    /**
     * @brief Construct a new lcd control::lcd control object for 4 bit mode
     * 
     * @param _RS The Register select pin of the lcd
     * @param _E  The enable pin of the lcd
     * @param _D4 The fifth data pin of the lcd
     * @param _D5 The sixth data pin of the lcd
     * @param _D6 The seventh data pin of the lcd
     * @param _D7 The eight data pin of the lcd
     * 
     * @details constructor for the use of 4 bit mode lcd. The class gets initialized for four bit mode.
     */
    LCD_Control::LCD_Control(gpio_num_t _RS, gpio_num_t _E, gpio_num_t _D4, gpio_num_t _D5, gpio_num_t _D6, gpio_num_t _D7)
        : LCD_RS(_RS), LCD_E(_E), LCD_D4(_D4), LCD_D5(_D5), LCD_D6(_D6), LCD_D7(_D7)
    {
        BitMode = FourBitMode;
        LCD_Initialize();
    }
    /**
     * @brief Destroy the lcd control::lcd control object
     * 
     * @details Destructor to set the output of the pins back to zero after destruction of the object. 
     * Mainly to remove any glitches when shutting down and restarting
     */
    LCD_Control::~LCD_Control(){
        std::string lcd_off = "00000000";
        LCD_Write(lcd_off,0);
        SetLow(LCD_E);
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
        for (int i =0; i < Data_String_.size(); i++)
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
        vTaskDelay(50/portTICK_PERIOD_MS);

        InitializeGPIO(LCD_E);
        SetLow(LCD_E);

        InitializeGPIO(LCD_RS);
        InitializeGPIO(LCD_D0);
        InitializeGPIO(LCD_D1);
        InitializeGPIO(LCD_D2);
        InitializeGPIO(LCD_D3);
        InitializeGPIO(LCD_D4);
        InitializeGPIO(LCD_D5);
        InitializeGPIO(LCD_D6);
        InitializeGPIO(LCD_D7);
    }

    /**
     * @brief Writes a binary std string to the lcd.
     * 
     * @param BinaryString The binary string that will be set on the lcd pins.
     * @param RS If the command needs to be written as data or register
     * 
     * @details Based on four or eight bit mode the function sets the binary string correct on the lcd pins and pulses the enable pin. 
     * It also set the rs pin based on the input parameter RS. This will make sure that the correct mode is used. 
     * The modes are register write and write to lcd. 
     */
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