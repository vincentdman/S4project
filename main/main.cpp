/**
 * @file main.cpp
 * @author Vincent de Man
 * @brief Main application for S4 Project (.cpp)
 * @version 1.1
 * @date 2021-03-24
 * @copyright Copyright (cpp) 2021
 * @details main.cpp main code for project S4  
 */
#include "main.h"


 extern "C" void app_main(void)
 {


   while(1){

   }

 }





  //TODO things to implement:
  //TODO Guideline: Don’t copy your function arguments. Instead, pass them by value and let the compiler do the copying.
  //TODO private stuff should have underscores
  //TODO default pointer p_pointer
  //TODO hal sensor adc class
  //TODO lcd class lcd_commands.h update
  //TODO lcd class pinout_t remove i2c ports
  //TODO header files uit implementatie halen

  //TODO things to learn:
  //TODO constexpr
  //TODO rule of three / five
  //TODO static functions
  //TODO enum class strongly typed
  //TODO move semantics
  //TODO perfect forwarding and reference collapsing
//}






//extern "C" void app_main(void)
// {
//   ESP_LOGI(TAG, "\n\nBuild version: %.2f\n", Build_Version);
//   ESP_LOGI(TAG, "Created by Vincent de Man\n");

//   LCD_Pinout_t Configs;
//   Configs._BitMode = I2CMode;
//   Configs._SDA = GPIO_NUM_21;
//   Configs._SCL = GPIO_NUM_22;
  

//   HandleI2C I2c(true);
//   LCD_Control LCD(Configs);
//   RGB_Control LED(GPIO_NUM_23,GPIO_NUM_19,GPIO_NUM_4);
//   HandleBMP180 BMP;

//   LCD.LCD_Write_Command(LCD_DISPLAY_ON_CURSOR_OFF);
//   LCD.LCD_Write_Command(LCD_CLEAR);


//   while (1)
//   {
//     LCD.LCD_Write_Command(LCD_HOME);
//     LCD.LCD_Write_String("Temperature:");
//     LCD.LCD_Write_Float(BMP.GetTemperature());
//     LCD.LCD_Write_Command(LCD_NEXT_LINE);
    
//     LCD.LCD_Write_String("Pressure: ");
//     LCD.LCD_Write_Float(BMP.GetPressure());
    
//     LED.SetRGB(rand()%100,rand()%100,rand()%100);
//     vTaskDelay(1000 / portTICK_PERIOD_MS);
//   }
// }