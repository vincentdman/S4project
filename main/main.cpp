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
   HandleHID HID(GPIO_NUM_4);
   while(1)
   {
     ESP_LOGI(TAG, "state : %d",HID.GetState());
     vTaskDelay(100/portTICK_PERIOD_MS);
   }

 }






 

  //TODO things to implement:
  //TODO private stuff should have underscores
  //TODO hal sensor adc class
  //TODO lcd class lcd_commands.h update (maybe flags)
  //TODO lcd class pinout_t remove i2c ports (not necesarry )
  //TODO SD card library

  //TODO things to learn:
  //TODO constexpr
  //TODO rule of three / five
  //TODO static functions
  //TODO enum class strongly typed
  //TODO move semantics
  //TODO perfect forwarding and reference collapsing
//}






