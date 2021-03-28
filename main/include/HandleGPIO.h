/**
 * @file HandleGPIO.h
 * @author Vincent de Man
 * @brief Header file for GPIO handler (.h)
 * @version 0.1
 * @date 2021-03-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef HandleGPIO_h
#define HandleGPIO_h

#include "esp_err.h"
#include "esp_system.h"
#include <driver/gpio.h>

extern "C"
{

  class HandleGPIO
  {
 
  public:

    HandleGPIO(); //default constructor

    void SetHigh(gpio_num_t);
    void SetLow(gpio_num_t);
    void InitializeGPIO(gpio_num_t);
  };
}

#endif