/**
 * @file LCD_Control.h
 * @author Vincent de Man
 * @brief Header file for the LCD_Control Class
 * @version 1.1
 * @date 2021-03-29
 * @details LCD_Control header for the use of the lcd class. Includes all the most important functions
 * @copyright Copyright (cpp) 2021
 * 
 */
#ifndef LCD_Control_h
#define LCD_Control_h

#include "HandleGPIO.h"
#include <driver/gpio.h>
#include <string>
#include "LCD_Commands.h"
#include <functional>

extern "C"
{
    class LCD_Control : private HandleGPIO
    {
    public:
        typedef enum
        {
            NotSelected = -1,
            FourBitMode = 0,
            EightBitMode = 1,

        } BitMode_t;

        typedef struct
        {
            gpio_num_t _RS = GPIO_NUM_NC;
            gpio_num_t _E = GPIO_NUM_NC;
            gpio_num_t _D0 = GPIO_NUM_NC;
            gpio_num_t _D1 = GPIO_NUM_NC;
            gpio_num_t _D2 = GPIO_NUM_NC;
            gpio_num_t _D3 = GPIO_NUM_NC;
            gpio_num_t _D4 = GPIO_NUM_NC;
            gpio_num_t _D5 = GPIO_NUM_NC;
            gpio_num_t _D6 = GPIO_NUM_NC;
            gpio_num_t _D7 = GPIO_NUM_NC;
            BitMode_t _BitMode = NotSelected;
        } LCD_Pinout_t;

        LCD_Control(LCD_Pinout_t &LCD_Pinout_Configuration);

        void LCD_Write_Char(char Data);
        void LCD_Initialize();
        void LCD_InitializeEightBitMode();
        void LCD_InitializeFourBitMode();
        void LCD_Write_Command(int Command);
        void LCD_Write_String(std::string Data_String_);
        void LCD_Write(std::string BinaryString, int RS);

        void LCD_WriteFourBitMode(std::string BinaryString, int RS);
        void LCD_WriteEightBitMode(std::string BinaryString, int RS);

    private:
        void LCD_InitializeForSendingData(int RS);
        void LCD_CycleDataTrough(void);
        void LCD_SetDataEightBitMode(std::string BinaryString);
        void LCD_SetDataFourBitModeFirstHalf(std::string BinaryString);
        void LCD_SetDataFourBitModeSecondHalf(std::string BinaryString);

        std::function<void(LCD_Control *, std::string BinaryString, int RS)> SwapWRITE = &LCD_Control::LCD_WriteEightBitMode;
        std::function<void(LCD_Control *)> SwapInitialize = &LCD_Control::LCD_InitializeEightBitMode;
        void SetBitMode();

        enum
        {
            RegisterSet = 0,
            WriteAction
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

        BitMode_t BitMode;
    };
}
#endif
