/**
 * @file LCD_Control.h
 * @author Vincent de Man
 * @brief Header file for the LCD_Control Class (.h).
 * @version 1.1
 * @date 2021-03-29
 * @details LCD_Control header for the use of the lcd class. Includes all of the most important functions
 * @copyright Copyright (cpp) 2021
 * 
 */
#ifndef LCD_Control_h
#define LCD_Control_h

#include "LCD_Commands.h"
#include "HandleGPIO.h"
#include "HandleI2C.h"
#include "driver/i2c.h"
#include <driver/gpio.h>
#include <string>
#include <functional>

extern "C"
{
    typedef enum
    {
        NotSelected = -1,
        FourBitMode = 0,
        EightBitMode = 1,
        I2CMode = 2,

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
        gpio_num_t _SCL = GPIO_NUM_NC;
        gpio_num_t _SDA = GPIO_NUM_NC;
        BitMode_t _BitMode = NotSelected;
    } LCD_Pinout_t;

    class LCD_Control : private HandleGPIO
    {
    public:
        const uint8_t LCD_Adress = 0x27;

        LCD_Control(LCD_Pinout_t &LCD_Pinout_Configuration);

        void LCD_Write_Char(char Data);
        void LCD_Initialize();

        esp_err_t LCD_InitializeEightBitMode();
        esp_err_t LCD_InitializeFourBitMode();
        esp_err_t LCD_InitializeI2CMode();
        esp_err_t LCD_Init_Sequence_4_Bit();
        esp_err_t LCD_Init_Sequence_8_Bit();


        void LCD_Write_Command(int Command);
        void LCD_Write_String(std::string Data_String_);
        void LCD_Write(std::string BinaryString, int RS);

    private:
        esp_err_t LCD_WriteFourBitMode(std::string BinaryString, int RS);
        esp_err_t LCD_WriteEightBitMode(std::string BinaryString, int RS);
        void LCD_WriteI2CMode(std::string BinaryString, int RS);

        esp_err_t LCD_Private_I2C_Send(uint8_t DataToSend);
        esp_err_t LCD_InitializeForSendingData(int RS);
        esp_err_t LCD_CycleDataTrough(void);

        esp_err_t LCD_SetDataEightBitMode(std::string BinaryString);
        esp_err_t LCD_SetDataFourBitModeFirstHalf(std::string BinaryString);
        esp_err_t LCD_SetDataFourBitModeSecondHalf(std::string BinaryString);

        void SetBitMode();

        std::function<void(LCD_Control *, std::string BinaryString, int RS)> SwapWRITE = &LCD_Control::LCD_WriteEightBitMode;
        std::function<void(LCD_Control *)> SwapInitialize = &LCD_Control::LCD_InitializeEightBitMode;

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

        gpio_num_t LCD_SCL = GPIO_NUM_NC;
        gpio_num_t LCD_SDA = GPIO_NUM_NC;

        BitMode_t BitMode;

        i2c_port_t I2C_Port = I2C_NUM_1;

        constexpr static const char* TAG = "LCD";
    };
}
#endif
