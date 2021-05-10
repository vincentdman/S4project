/**
 * @file LCD_Control.cpp
 * @author Vincent de Man
 * @brief Source file for LCD_Control class.
 * @version 2.1
 * @date 2021-03-29
 * @class LCD_Control class to use a lcd display easily.
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
#include <driver/i2c.h>

extern "C"
{
    /**
     * @brief Construct a new lcd control::lcd control object
     * 
     * @details Constructor takes in a LCD_Pinout_t constructor the user needs to initialize the used pins for the lcd in the structure
     * 
     * @param LCD_Pinout_Configuration Structure that has all the used pins for the lcd in it. 
     */
    LCD_Control::LCD_Control(LCD_Pinout_t &LCD_Pinout_Configuration)
        : LCD_RS(LCD_Pinout_Configuration._RS), LCD_E(LCD_Pinout_Configuration._E),
          LCD_D0(LCD_Pinout_Configuration._D0), LCD_D1(LCD_Pinout_Configuration._D1), LCD_D2(LCD_Pinout_Configuration._D2), LCD_D3(LCD_Pinout_Configuration._D3),
          LCD_D4(LCD_Pinout_Configuration._D4), LCD_D5(LCD_Pinout_Configuration._D5), LCD_D6(LCD_Pinout_Configuration._D6), LCD_D7(LCD_Pinout_Configuration._D7),
          LCD_SCL(LCD_Pinout_Configuration._SCL), LCD_SDA(LCD_Pinout_Configuration._SDA), BitMode(LCD_Pinout_Configuration._BitMode)
    {   
        //std::cout<<"LCD Needs time to start up...."<<std::endl;
        
        

        SetBitMode();
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
     * @brief Function that swaps the initialize four bit and eight bit mode 
     * 
     * @details Function that uses the std::function to switch between eight and four bit mode. 
     */
    void LCD_Control::LCD_Initialize()
    {
        SwapInitialize(this);
    }

    /**
     * @brief Initialize function for four bit mode
     * 
     * @details function that gets called when the lcd is in four bit mode
     */
    void LCD_Control::LCD_InitializeFourBitMode()
    {

        vTaskDelay(50 / portTICK_PERIOD_MS);

        InitializeGPIO(LCD_E);
        SetLow(LCD_E);
        InitializeGPIO(LCD_RS);
        InitializeGPIO(LCD_D7);
        InitializeGPIO(LCD_D6);
        InitializeGPIO(LCD_D5);
        InitializeGPIO(LCD_D4);
    }

    /**
     * @brief Initialize function for eight bit mode
     * 
     * @details function that gets called when the lcd is in eight bit mode
     */
    void LCD_Control::LCD_InitializeEightBitMode()
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

    /**
     * @brief Function to write to the lcd.
     * 
     * @param BinaryString The data in a binary string that gets put on the lcd.
     * @param RS Choice between writing to the lcd and writing to the registers.
     * 
     * @details Function that swaps between write eight bits and write four bits.
     */
    void LCD_Control::LCD_Write(std::string BinaryString, int RS)
    {
        SwapWRITE(this, BinaryString, RS);
    }

    /**
     * @brief Function to switch between the functions for four and eight bit.
     * 
     * @details Function that switches between the functions for four and eight bit mode. This gets called once when the constructor is called. 
     */
    void LCD_Control::SetBitMode()
    {
        if (BitMode == FourBitMode)
        {
            SwapInitialize = &LCD_Control::LCD_InitializeFourBitMode;
            SwapWRITE = &LCD_Control::LCD_WriteFourBitMode;
        }
        else if (BitMode == EightBitMode)
        {
            SwapInitialize = &LCD_Control::LCD_InitializeEightBitMode;
            SwapWRITE = &LCD_Control::LCD_WriteEightBitMode;
        }
        else if (BitMode == I2CMode)
        {
            SwapInitialize = &LCD_Control::LCD_InitializeI2CMode;
            SwapWRITE = &LCD_Control::LCD_WriteI2CMode;
        }
        else
        {
            ///make error
            //todo
            //esp error maybe :)
        }
    }

    void LCD_Control::LCD_InitializeI2CMode()
    {

        
    //         //                  0b7654xEWS
    //      // uint8_t WriteData = 0b00000000; //default settings
    //         uint8_t WriteData = 0b00000000;
    //         uint8_t WriteDataZero = 0b00000000;

    //     i2c_cmd_handle_t link_cmd = i2c_cmd_link_create();
    //     i2c_master_start(link_cmd);
    //     i2c_master_write_byte(link_cmd, (LCD_Adress<<1) | I2C_MASTER_WRITE , true);
        
    //     //Set pins as output mode
    //     i2c_master_write(link_cmd, &WriteDataZero, sizeof(WriteDataZero), true);

    //     //set RS level according to input RS
    //     i2c_master_write(link_cmd, &WriteData, sizeof(WriteData) , true);
        
    //     i2c_master_stop(link_cmd);
    //     i2c_master_cmd_begin(I2C_Port, link_cmd, 1000 / portTICK_RATE_MS);
    //     i2c_cmd_link_delete(link_cmd);



    // std::cout << "succes"<<std::endl;


//end of test code


        

          //                  0b7654xEWS
        //uint8_t WriteData = 0b00000000;
        

        ets_delay_us(100000); // init delay 100ms




        uint8_t EnableHigh = 0b00111100;
        
       i2c_cmd_handle_t link_cmd = i2c_cmd_link_create();
        i2c_master_start(link_cmd);
        i2c_master_write_byte(link_cmd, (LCD_Adress<<1) | I2C_MASTER_WRITE , true);
        

        i2c_master_write(link_cmd, &EnableHigh, sizeof(EnableHigh) , true);
        
        i2c_master_stop(link_cmd);
        i2c_master_cmd_begin(I2C_Port, link_cmd, 1000 / portTICK_RATE_MS);
        i2c_cmd_link_delete(link_cmd);

        ets_delay_us(270);




        ets_delay_us(300);
        uint8_t enablelowpulse = 0b00111000;
        
        link_cmd = i2c_cmd_link_create();
        i2c_master_start(link_cmd);
        i2c_master_write_byte(link_cmd, (LCD_Adress<<1) | I2C_MASTER_WRITE , true);
        

        i2c_master_write(link_cmd, &enablelowpulse, sizeof(enablelowpulse) , true);
        
        i2c_master_stop(link_cmd);
        i2c_master_cmd_begin(I2C_Port, link_cmd, 1000 / portTICK_RATE_MS);
        i2c_cmd_link_delete(link_cmd);

      

        ets_delay_us(4500);




/////////////////////////////////////////////////////////////////////






        EnableHigh |= 0b00111100;
        
        link_cmd = i2c_cmd_link_create();
        i2c_master_start(link_cmd);
        i2c_master_write_byte(link_cmd, (LCD_Adress<<1) | I2C_MASTER_WRITE , true);
        

        i2c_master_write(link_cmd, &EnableHigh, sizeof(EnableHigh) , true);
        
        i2c_master_stop(link_cmd);
        i2c_master_cmd_begin(I2C_Port, link_cmd, 1000 / portTICK_RATE_MS);
        i2c_cmd_link_delete(link_cmd);

        ets_delay_us(270);

      ets_delay_us(300);
       enablelowpulse = 0b00111000;
        
        link_cmd = i2c_cmd_link_create();
        i2c_master_start(link_cmd);
        i2c_master_write_byte(link_cmd, (LCD_Adress<<1) | I2C_MASTER_WRITE , true);
        

        i2c_master_write(link_cmd, &enablelowpulse, sizeof(enablelowpulse) , true);
        
        i2c_master_stop(link_cmd);
        i2c_master_cmd_begin(I2C_Port, link_cmd, 1000 / portTICK_RATE_MS);
        i2c_cmd_link_delete(link_cmd);

      

        ets_delay_us(200);


        /////////////////////////////////////////////////////////////

          EnableHigh |= 0b00111100;
        
        link_cmd = i2c_cmd_link_create();
        i2c_master_start(link_cmd);
        i2c_master_write_byte(link_cmd, (LCD_Adress<<1) | I2C_MASTER_WRITE , true);
        

        i2c_master_write(link_cmd, &EnableHigh, sizeof(EnableHigh) , true);
        
        i2c_master_stop(link_cmd);
        i2c_master_cmd_begin(I2C_Port, link_cmd, 1000 / portTICK_RATE_MS);
        i2c_cmd_link_delete(link_cmd);

        ets_delay_us(270);

      ets_delay_us(300);
       enablelowpulse = 0b00111000;
        
        link_cmd = i2c_cmd_link_create();
        i2c_master_start(link_cmd);
        i2c_master_write_byte(link_cmd, (LCD_Adress<<1) | I2C_MASTER_WRITE , true);
        

        i2c_master_write(link_cmd, &enablelowpulse, sizeof(enablelowpulse) , true);
        
        i2c_master_stop(link_cmd);
        i2c_master_cmd_begin(I2C_Port, link_cmd, 1000 / portTICK_RATE_MS);
        i2c_cmd_link_delete(link_cmd);

      

        ets_delay_us(200);


        /////////////////////////////////////////////////////////////////

             EnableHigh = 0b00101100;
        
        link_cmd = i2c_cmd_link_create();
        i2c_master_start(link_cmd);
        i2c_master_write_byte(link_cmd, (LCD_Adress<<1) | I2C_MASTER_WRITE , true);
        

        i2c_master_write(link_cmd, &EnableHigh, sizeof(EnableHigh) , true);
        
        i2c_master_stop(link_cmd);
        i2c_master_cmd_begin(I2C_Port, link_cmd, 1000 / portTICK_RATE_MS);
        i2c_cmd_link_delete(link_cmd);

        ets_delay_us(270);

      ets_delay_us(300);
       enablelowpulse = 0b00101000;
        
        link_cmd = i2c_cmd_link_create();
        i2c_master_start(link_cmd);
        i2c_master_write_byte(link_cmd, (LCD_Adress<<1) | I2C_MASTER_WRITE , true);
        

        i2c_master_write(link_cmd, &enablelowpulse, sizeof(enablelowpulse) , true);
        
        i2c_master_stop(link_cmd);
        i2c_master_cmd_begin(I2C_Port, link_cmd, 1000 / portTICK_RATE_MS);
        i2c_cmd_link_delete(link_cmd);

      

        ets_delay_us(200);


        //////////////////////////////////////////////////////////////////////////





    }

    void LCD_Control::LCD_WriteI2CMode(std::string BinaryString, int RS)
    {
            //test code
            //uint8_t DataADRR = 0x40; 

        ets_delay_us(240);

          //                  0b7654xEWS
        //uint8_t WriteData = 0b00000000;
        uint8_t WriteRS   = RS;

        ets_delay_us(1000);

        i2c_cmd_handle_t link_cmd = i2c_cmd_link_create();
        i2c_master_start(link_cmd);
        i2c_master_write_byte(link_cmd, (LCD_Adress<<1) | I2C_MASTER_WRITE , true);
        
       

        i2c_master_write(link_cmd, &WriteRS, sizeof(WriteRS), true);
        
        i2c_master_stop(link_cmd);
        i2c_master_cmd_begin(I2C_Port, link_cmd, 1000 / portTICK_RATE_MS);
        i2c_cmd_link_delete(link_cmd);

        ets_delay_us(270);







        uint8_t EnableHigh = WriteRS;
        EnableHigh |= 0b00001100;

        link_cmd = i2c_cmd_link_create();
        i2c_master_start(link_cmd);
        i2c_master_write_byte(link_cmd, (LCD_Adress<<1) | I2C_MASTER_WRITE , true);
        

        i2c_master_write(link_cmd, &EnableHigh, sizeof(EnableHigh) , true);
        
        i2c_master_stop(link_cmd);
        i2c_master_cmd_begin(I2C_Port, link_cmd, 1000 / portTICK_RATE_MS);
        i2c_cmd_link_delete(link_cmd);

        ets_delay_us(270);






        uint8_t FirstHalf = EnableHigh;
        uint8_t Data  = ((BinaryString[0] - '0')<<3);
                Data |= ((BinaryString[1] - '0')<<2);
                Data |= ((BinaryString[2] - '0')<<1);
                Data |= ((BinaryString[3] - '0')<<0);
                Data = Data<<4;
        FirstHalf |= Data;       

        link_cmd = i2c_cmd_link_create();
        i2c_master_start(link_cmd);
        i2c_master_write_byte(link_cmd, (LCD_Adress<<1) | I2C_MASTER_WRITE , true);
        

        i2c_master_write(link_cmd, &FirstHalf, sizeof(FirstHalf), true);
        
        i2c_master_stop(link_cmd);
        i2c_master_cmd_begin(I2C_Port, link_cmd, 1000 / portTICK_RATE_MS);
        i2c_cmd_link_delete(link_cmd);





        ets_delay_us(300);
        uint8_t enablelowpulse = FirstHalf;
        enablelowpulse &= ~(0b00000100) ;
        link_cmd = i2c_cmd_link_create();
        i2c_master_start(link_cmd);
        i2c_master_write_byte(link_cmd, (LCD_Adress<<1) | I2C_MASTER_WRITE , true);
        

        i2c_master_write(link_cmd, &enablelowpulse, sizeof(enablelowpulse) , true);
        
        i2c_master_stop(link_cmd);
        i2c_master_cmd_begin(I2C_Port, link_cmd, 1000 / portTICK_RATE_MS);
        i2c_cmd_link_delete(link_cmd);

       // ets_delay_us(1000);

        ets_delay_us(300);

       






        uint8_t enablehighpulse = EnableHigh;
        enablehighpulse |= Data;
        link_cmd = i2c_cmd_link_create();
        i2c_master_start(link_cmd);
        i2c_master_write_byte(link_cmd, (LCD_Adress<<1) | I2C_MASTER_WRITE , true);
        


        i2c_master_write(link_cmd, &enablehighpulse, sizeof(enablehighpulse) , true);
        
        i2c_master_stop(link_cmd);
        i2c_master_cmd_begin(I2C_Port, link_cmd, 1000 / portTICK_RATE_MS);
        i2c_cmd_link_delete(link_cmd);

        ets_delay_us(270);




        uint8_t SecondHalf = EnableHigh;
        uint8_t Data2  = ((BinaryString[4] - '0')<<3);
                Data2 |= ((BinaryString[5] - '0')<<2);
                Data2 |= ((BinaryString[6] - '0')<<1);
                Data2 |= ((BinaryString[7] - '0')<<0);
                Data2 = Data2<<4;
        SecondHalf |= Data2;       

        link_cmd = i2c_cmd_link_create();
        i2c_master_start(link_cmd);
        i2c_master_write_byte(link_cmd, (LCD_Adress<<1) | I2C_MASTER_WRITE , true);
        
      

        i2c_master_write(link_cmd, &SecondHalf, sizeof(SecondHalf) , true);
        
        i2c_master_stop(link_cmd);
        i2c_master_cmd_begin(I2C_Port, link_cmd, 1000 / portTICK_RATE_MS);
        i2c_cmd_link_delete(link_cmd);



            ets_delay_us(300);




        uint8_t enablelowpulse2 = SecondHalf;
        enablelowpulse2 &= ~(0b00000100) ;
        link_cmd = i2c_cmd_link_create();
        i2c_master_start(link_cmd);
        i2c_master_write_byte(link_cmd, (LCD_Adress<<1) | I2C_MASTER_WRITE , true);
        
        i2c_master_write(link_cmd, &enablelowpulse2, sizeof(enablelowpulse2) , true);
        
        i2c_master_stop(link_cmd);
        i2c_master_cmd_begin(I2C_Port, link_cmd, 1000 / portTICK_RATE_MS);
        i2c_cmd_link_delete(link_cmd);



          ets_delay_us(1000);
        

       

    }

    /**
     * @brief Function to write in four bit mode to the lcd
     * 
     * @param BinaryString The bitstring that gets written to the lcd.
     * @param RS The mode the write action will be in (write to register or write to the lcd)
     * 
     * @details Function to write to the lcd in four bit mode. 
     */
    void LCD_Control::LCD_WriteFourBitMode(std::string BinaryString, int RS)
    {
        LCD_InitializeForSendingData(RS);
        LCD_SetDataFourBitModeFirstHalf(BinaryString);
        LCD_CycleDataTrough();
        LCD_SetDataFourBitModeSecondHalf(BinaryString);
        LCD_CycleDataTrough();
    }

    /**
     * @brief Function to write in eight bit mode to the lcd
     * 
     * @param BinaryString The bitstring that gets written to the lcd.
     * @param RS The mode the write action will be in (write to register or write to the lcd)
     * 
     * @details Function to write to the lcd in eight bit mode. 
     */
    void LCD_Control::LCD_WriteEightBitMode(std::string BinaryString, int RS)
    {
        LCD_InitializeForSendingData(RS);
        LCD_SetDataEightBitMode(BinaryString);
        LCD_CycleDataTrough();
    }

    /**
     * @brief Function to initialize the lcd for sending sending data.
     * 
     * @param RS The mode the write action will be in (write to register or write to the lcd)
     * 
     * @details Function that makes the lcd ready for sending data. By setting enable high and setting the RS pin according to input parameter.
     */
    void LCD_Control::LCD_InitializeForSendingData(int RS)
    {
        ets_delay_us(1000);
        gpio_set_level(LCD_RS, RS);
        ets_delay_us(270);
        SetHigh(LCD_E);
        ets_delay_us(240);
    }

    /**
     * @brief Function to cycle the data trough to the lcd.
     * 
     * @details Function to cycle the data trought to the lcd by making a falling edge on the enable pin.
     */
    void LCD_Control::LCD_CycleDataTrough(void)
    {
        ets_delay_us(300);
        SetLow(LCD_E);
        ets_delay_us(1000);
    }

    /**
     * @brief Function to set the lcd data ready on the lcd pins for eight bit mode.
     * 
     * @param BinaryString Data that gets put on the lcd pins.
     * 
     * @details Function that sets the lcd data ready on the pins by using gpio_set_level().  
     */
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

    /**
     * @brief Function to set the first half of the binary string on the lcd pins in four bit mode.
     * 
     * @param BinaryString The data in a bit string that gets set on the lcd. 
     * 
     * @details Function to set the first half of the binary string on the lcd pins in four bit mode.
     */
    void LCD_Control::LCD_SetDataFourBitModeFirstHalf(std::string BinaryString)
    {
        gpio_set_level(LCD_D4, BinaryString[3] - '0');
        gpio_set_level(LCD_D5, BinaryString[2] - '0');
        gpio_set_level(LCD_D6, BinaryString[1] - '0');
        gpio_set_level(LCD_D7, BinaryString[0] - '0');
    }

    /**
     * @brief Function to set the second half to the lcd pins in four bit mode.
     * 
     * @param BinaryString The data in a bit string that gets set on the lcd. 
     * 
     * @details Function to set the second half to the lcd pins in four bit mode.
     */
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