/**
 * @file main.cpp
 * @author Vincent de Man
 * @brief Main application for S4 Project (.cpp)
 * @version 0.1
 * @date 2021-03-24
 * 
 * @copyright Copyright (c) 2021
 * @details main.cpp main code for project S4  
 */
#include <stdio.h>
#include <iostream>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include <driver/gpio.h>
#include <driver/adc.h>
#include <esp_wifi.h>
#include "HandleGPIO.h"
#include "RGB_Control.h"
#include "PWM_GPIO.h"
#include "LCD_Commands.h"
#include "LCD_Control.h"
#include <string>

extern "C" void app_main(void)
{


  // std::cout<<"Hello world!"<<std::endl;

   //PWM_GPIO a;
   // working gpio
   //LCD_Control a(GPIO_NUM_2,GPIO_NUM_15,GPIO_NUM_33,GPIO_NUM_25,GPIO_NUM_26,GPIO_NUM_4,GPIO_NUM_19,GPIO_NUM_21,GPIO_NUM_5,GPIO_NUM_27);
    LCD_Control UnitTestLCD(GPIO_NUM_2,GPIO_NUM_21,GPIO_NUM_25,GPIO_NUM_26,GPIO_NUM_19,GPIO_NUM_27);                      
   //  std::string commands = "00000010";
   //  a.LCD_Write(commands,0);
   
   //  commands = "00101000";
   //  a.LCD_Write(commands,0);

   //  commands = "00001100";
   //  a.LCD_Write(commands,0);

   //  commands = "00000010";
   //  a.LCD_Write(commands,0);

   //  commands = "00000110";
   //  a.LCD_Write(commands,0);

   //  commands = "00000001";
   //  a.LCD_Write(commands,0);

   //  commands = "10000000";
   //  a.LCD_Write(commands,0);

    //a.LCD_Write_Command(LCD_4_BIT_MODE);
    //a.LCD_Write_Char('a');
    //a.LCD_Write_Char('b');
    //a.LCD_Write_Char('c');
    //a.LCD_Write_Char('d');

    // commands = "00000000";
    // a.LCD_Write(commands,0);
    // commands = "00001110";
    // a.LCD_Write(commands,0);
    // commands = "10000000";  
    // a.LCD_Write("01000001",1);

   //std::cout<<"constructor"<<std::endl;



    UnitTestLCD.LCD_Write_Command(LCD_4_BIT_MODE);
    UnitTestLCD.LCD_Write_Command(LCD_DISPLAY_ON_CURSOR_OFF);
    UnitTestLCD.LCD_Write_Command(LCD_CLEAR);
    UnitTestLCD.LCD_Write_Command(LCD_HOME);
    
    UnitTestLCD.LCD_Write_Char('a');
    UnitTestLCD.LCD_Write_Char('B');
    UnitTestLCD.LCD_Write_Char('c');

    UnitTestLCD.LCD_Write_Command(LCD_NEXT_LINE);

    std::string hello = "hello world!";
    UnitTestLCD.LCD_Write_String(hello);
   
   

   //std::cout<<"put string"<<std::endl;
   //a.LCD_Write_Char('a');
   //a.LCD_Write_Char('B');
   //a.LCD_Write_Char('c');
   //std::cout<<"put a"<<std::endl;


   //a.SetDuty(40);
   // a.PWM_Initialize(GPIO_NUM_26);
   // a.PWM_Initialize(GPIO_NUM_25);
   //a.PWM_Initialize(GPIO_NUM_27);
   
   //while (1)
   // {
   //a.SetDuty(0,GPIO_NUM_25);
   //a.SetDuty(34,GPIO_NUM_27);
   // for (int i=0; i < 100; i += 10)
   // {
   // a.SetDuty(i,GPIO_NUM_26);

   //  a.UpdateTimerConfig();
   //  vTaskDelay(1000 / portTICK_PERIOD_MS);
   // }
   // }
   //HandleGPIO a;
   //a.SetHigh(GPIO_NUM_4);
  // RGB_Control RGB_LED(GPIO_NUM_25, GPIO_NUM_26, GPIO_NUM_27);

   //RGB_LED.SetRGB(100, 50, 0);
   /*
   while (1)
   {
      RGB_LED.SetRed();
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      RGB_LED.SetBlue();
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      RGB_LED.SetGreen();
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      RGB_LED.SetPurple();
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      RGB_LED.SetCyan();
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      RGB_LED.SetYellow();
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      RGB_LED.SetWhite();
      vTaskDelay(1000 / portTICK_PERIOD_MS);
   }
   */
}
