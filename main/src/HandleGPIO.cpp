/**
 * @file HandleGPIO.cpp
 * @author Vincent de Man
 * @brief Basic GPIO class (.cpp)
 * @version 0.1
 * @date 2021-03-24
 * @copyright Copyright (c) 2021
 * @class HandleGPIO class to add basic gpio functionality to objects
 * 
 */
#include "HandleGPIO.h"
#include <iostream>
#include <driver/gpio.h>
#include "esp_err.h"
#include "esp_system.h"

extern "C"
{
    /**
     * @brief Construct a new Handle GPIO::HandleGPIO object
     * 
     */
    HandleGPIO::HandleGPIO()
    {
        std::cout << "test";
    }
    /**
     * @brief Initialize a gpio pin for default settings
     * 
     * @param PIN 
     */
    void HandleGPIO::InitializeGPIO(gpio_num_t PIN)
    {
        gpio_set_pull_mode(PIN, GPIO_PULLDOWN_ONLY);
        gpio_set_direction(PIN, GPIO_MODE_OUTPUT);
    }
    /**
     * @brief function to set the given pin high
     * 
     * @param PIN 
     */
    void HandleGPIO::SetHigh(gpio_num_t PIN)
    {
        gpio_set_level(PIN, 1);
    }
    /**
     * @brief function to set the given pin low
     * 
     * @param PIN 
     */
    void HandleGPIO::SetLow(gpio_num_t PIN)
    {
        gpio_set_level(PIN, 0);
    }
}