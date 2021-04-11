/**
 * @file LCD_Control.h
 * @author Vincent de Man
 * @brief 
 * @version 0.1
 * @date 2021-03-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef LCD_Control_h
#define LCD_Control_h

#include "HandleGPIO.h"
#include <driver/gpio.h>
#include <string> 
#include "LCD_Commands.h"

extern "C"
{
class LCD_Control : private HandleGPIO {
    public:
        LCD_Control(gpio_num_t _RS, gpio_num_t _E, gpio_num_t _D0, gpio_num_t _D1, gpio_num_t _D2, gpio_num_t _D3, gpio_num_t _D4, gpio_num_t _D5, gpio_num_t _D6, gpio_num_t _D7);
        LCD_Control(gpio_num_t _RS, gpio_num_t _E, gpio_num_t _D4, gpio_num_t _D5 ,gpio_num_t _D6, gpio_num_t _D7);
        void LCD_Write_Char(char Data);
        void LCD_Initialize(); 
        void LCD_Write_Command(int Command);
        void LCD_Write_String(std::string Data_String_);
        void LCD_Write(std::string BinaryString,int RS);

    private:
    int BitMode = EightBitMode;
    enum{
        RegisterSet =0,
        WriteAction =1, 
        FourBitMode,
        EightBitMode
    };
    gpio_num_t LCD_RS = GPIO_NUM_NC;
    gpio_num_t LCD_E = GPIO_NUM_NC;

    gpio_num_t LCD_D0 = GPIO_NUM_NC;
    gpio_num_t LCD_D1 = GPIO_NUM_NC;
    gpio_num_t LCD_D2 = GPIO_NUM_NC;
    gpio_num_t LCD_D3 = GPIO_NUM_NC;
    gpio_num_t LCD_D4 = GPIO_NUM_NC;
    gpio_num_t LCD_D5 = GPIO_NUM_NC;
    gpio_num_t LCD_D6 = GPIO_NUM_NC;
    gpio_num_t LCD_D7 = GPIO_NUM_NC;



};



}
#endif
