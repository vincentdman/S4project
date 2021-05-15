/**
 * @file HandlePIN.cpp
 * @author Vincent de Man
 * @brief Source file for HandlePIN class (.cpp)
 * @version 0.1
 * @date 2021-05-15
 * @class HandlePIN class to handle one single pin. 
 * @copyright Copyright (c) 2021
 * @details Source file for HandlePIN class to make single pin objects. 
 */

#include "HandlePIN.h"


extern "C"{

    HandlePIN::HandlePIN(const gpio_num_t PIN, gpio_mode_t MODE, gpio_pull_mode_t PULL)
        :_PIN(PIN),_MODE(MODE),_PULL(PULL)
    {

    }
     esp_err_t HandlePIN::PIN_Initialize()
     {
         esp_err_t Error = ESP_OK;
         Error |= gpio_set_direction(_PIN,_MODE);
         Error |= gpio_set_pull_mode(_PIN,_PULL);
         return Error;
     }

    esp_err_t HandlePIN::PIN_High()
    {   
        esp_err_t Error = ESP_OK;
        Error |= gpio_set_level(_PIN, HIGH);
        return Error;
    }

     esp_err_t HandlePIN::PIN_Low()
    {   
        esp_err_t Error = ESP_OK;
        Error |= gpio_set_level(_PIN, LOW);
        return Error;
    }

    int HandlePIN::PIN_GetLevel()
    {
        return gpio_get_level(_PIN);
    }

    void HandlePIN::PIN_ChangeMode(const gpio_mode_t MODE)
    {
        _MODE = MODE; 
    }

    void HandlePIN::PIN_ChangePullMode(const gpio_pull_mode_t PULL)
    {
        _PULL = PULL; 
    }

    void HandlePIN::PIN_ChangeInt(const gpio_int_type_t INTR)
    {
        _INTR = INTR; 
    }

    gpio_num_t HandlePIN::PIN_GetNum()
    {
        return _PIN;
    }

    gpio_mode_t HandlePIN::PIN_GetMode()
    {
        return _MODE;
    }

    gpio_pull_mode_t HandlePIN::PIN_GetPull()
    {
        return _PULL;
    }

    gpio_int_type_t HandlePIN::PIN_GetIntr()
    {
        return _INTR; 
    }

}