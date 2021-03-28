/**
 * @file main.cpp
 * @author Vincent de Man
 * @brief Main application for S4 Project (.cpp)
 * @version 0.1
 * @date 2021-03-24
 * 
 * @copyright Copyright (c) 2021
 * 
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

extern "C" void app_main(void)
{

   std::cout << "Hello world!\n";

   //PWM_GPIO a;

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
   RGB_Control RGB_LED(GPIO_NUM_25, GPIO_NUM_26, GPIO_NUM_27);

   RGB_LED.SetRGB(100, 50, 0);
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
