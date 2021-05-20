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
   HandleJOYstick JOY(GPIO_NUM_15,GPIO_NUM_26,GPIO_NUM_4);
   RGB_Control RGB(GPIO_NUM_23,GPIO_NUM_19,GPIO_NUM_25);  
  
    int SetR = 0;
    int SetG = 0;
    int SetB = 0; 
   
   while(1)
   {
    //  JOY_Data_t t = JOY.GetConverted(); 
     
    //  SetR = t.VRX + 50; 
    //  SetG = t.VRY + 50;
    //  SetB = SetR * SetG / 100;
    //  RGB.SetRGB(SetR,SetG,SetB);
    ESP_LOGI(TAG,"test");

     vTaskDelay(1000/portTICK_PERIOD_MS);
   }

 }





  //TODO things to implement:
  //TODO Guideline: Don’t copy your function arguments. Instead, pass them by value and let the compiler do the copying.
  //TODO private stuff should have underscores
  //TODO hal sensor adc class
  //TODO lcd class lcd_commands.h update (maybe flags)
  //TODO lcd class pinout_t remove i2c ports (not necesarry )
  //TODO header files uit implementatie halen (.cpp)
  //TODO SD card library

  //TODO things to learn:
  //TODO constexpr
  //TODO rule of three / five
  //TODO static functions
  //TODO enum class strongly typed
  //TODO move semantics
  //TODO perfect forwarding and reference collapsing
//}






