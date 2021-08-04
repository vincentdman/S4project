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
     * 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     */
    esp_err_t HandleGPIO::InitializeGPIO_Output(const gpio_num_t PIN)
    {
        esp_err_t Error = ESP_OK; 
        Error |= gpio_set_pull_mode(PIN, GPIO_PULLDOWN_ONLY);
        Error |= gpio_set_direction(PIN, GPIO_MODE_OUTPUT);  
        ESP_LOGD(TAG,"Initialize PIN%d as output and pulldown enabled.\n",PIN);   
        return Error;
    }

    /**
     * @brief Function to initialize gpio for input. 
     * 
     * @param PIN The PIN that will be affected. 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value. 
     * 
     * @details Function to initialize gpio for input and gpio_pulldown
     */
    esp_err_t HandleGPIO::InitializeGPIO_Input(const gpio_num_t PIN)
    {
        esp_err_t Error = ESP_OK; 
        Error |= gpio_set_pull_mode(PIN, GPIO_PULLDOWN_ONLY);
        Error |= gpio_set_direction(PIN, GPIO_MODE_INPUT);  
        ESP_LOGD(TAG,"Initialize PIN%d as input and pulldown enabled.\n",PIN);   
        return Error;
    }

    /**
     * @brief function to set the given pin high
     * 
     * @param PIN The pin that gets set to high type is gpio_num_t
     * 
     * @details Function to set the ouput of a pin to high. It utalizes the gpio_set_level function and takes in the pin parameter.
     * 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     */
    esp_err_t HandleGPIO::SetHigh(const gpio_num_t PIN)
    {
        esp_err_t Error = ESP_OK; 
        Error |= gpio_set_level(PIN, 1);
        ESP_LOGD(TAG,"Set PIN%d high.\n",PIN);
        return Error;     
    }

    /**
     * @brief function to set the given pin low
     * 
     * @param PIN The pin that gets set to low type is gpio_num_t
     * 
     * @details Function to set the ouput of a pin to low. It utalizes the gpio_set_level function and takes in the pin parameter. 
     * 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     */
    esp_err_t HandleGPIO::SetLow(const gpio_num_t PIN)
    {
        esp_err_t Error = ESP_OK; 
        Error |= gpio_set_level(PIN, 0);
        ESP_LOGD(TAG,"Set PIN%d low.\n",PIN);
        return Error;     
    }

    /**
     * @brief Function to get the level of a gpio pin. 
     * 
     * @param PIN The slected pin. 
     * @return int return 0 is low return 1 is high.
     * 
     * @details Function to get the level of a gpio pin. When it is not a input it will give 0 back. 
     */
    int HandleGPIO::GetLevel(const gpio_num_t PIN)
    {
        return gpio_get_level(PIN);
    }
}