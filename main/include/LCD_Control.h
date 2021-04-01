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
        void LCD_Write_Command(int Command);
        void LCD_Write_String(std::string Data_String_);
        void LCD_Write(std::string BinaryString);

    private:
    int FourBitMode = 0;
    
    gpio_num_t LCD_RS;
    gpio_num_t LCD_E;

    gpio_num_t LCD_D0;
    gpio_num_t LCD_D1;
    gpio_num_t LCD_D2;
    gpio_num_t LCD_D3;
    gpio_num_t LCD_D4;
    gpio_num_t LCD_D5;
    gpio_num_t LCD_D6;
    gpio_num_t LCD_D7;



};



}
#endif
