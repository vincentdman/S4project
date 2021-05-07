/**
 * @file HandleGPIO.cpp
 * @author Vincent de Man
 * @brief Basic GPIO class (.cpp)
 * @version 1.1
 * @date 2021-03-24
 * @copyright Copyright (cpp) 2021
 * @class HandleGPIO class to add basic gpio functionality to objects.
 * @details Implementation of the handle gpio functions. It makes use of the esp-idf framework. 
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
     * @details Default constructor for Handle GPIO class. Doesn't take any inputs doesn't do anything
     */
    HandleGPIO::HandleGPIO()
    {
    }

    /**
     * @brief Initialize a gpio pin for default settings
     * 
     * @param PIN The pin that gets initialized type is gpio_num_t
     * 
     * @details function to initialize a gpio pin. Input is the gpio pint as type gpio_num_t. it sets the pulldown resistor as active and sets the GPIO mode as output.
     */
    void HandleGPIO::InitializeGPIO(gpio_num_t PIN)
    {
        gpio_set_pull_mode(PIN, GPIO_PULLDOWN_ONLY);
        gpio_set_direction(PIN, GPIO_MODE_OUTPUT);
    }

    /**
     * @brief function to set the given pin high
     * 
     * @param PIN The pin that gets set to high type is gpio_num_t
     * 
     * @details Function to set the ouput of a pin to high. It utalizes the gpio_set_level function and takes in the pin parameter.
     */
    void HandleGPIO::SetHigh(gpio_num_t PIN)
    {
        gpio_set_level(PIN, 1);
    }

    /**
     * @brief function to set the given pin low
     * 
     * @param PIN The pin that gets set to low type is gpio_num_t
     * 
     * @details Function to set the ouput of a pin to low. It utalizes the gpio_set_level function and takes in the pin parameter. 
     */
    void HandleGPIO::SetLow(gpio_num_t PIN)
    {
        gpio_set_level(PIN, 0);
    }
}