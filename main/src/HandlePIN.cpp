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
       if(!GPIO_IS_VALID_GPIO(_PIN))
       {
           ESP_LOGE(TAG,"ERROR pin isn't correct\n");
       } 
    }
    HandlePIN::~HandlePIN()
    {
        gpio_uninstall_isr_service();
        gpio_isr_handler_remove(_PIN);

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

    gpio_num_t HandlePIN::PIN_GetNum() const
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

    esp_err_t HandlePIN::PIN_Reset()
    {
        return gpio_reset_pin(_PIN);
    }

    esp_err_t HandlePIN::PIN_SetINTR()
    {
        return gpio_set_intr_type(_PIN,_INTR);
    }

    esp_err_t HandlePIN::PIN_EnableINTR()
    {
        return gpio_intr_enable(_PIN);
    }

    esp_err_t HandlePIN::PIN_DisableINTR()
    {
        return gpio_intr_disable(_PIN);
    }

    esp_err_t HandlePIN::PIN_InstallISR(int flags)
    {
        return gpio_install_isr_service(flags);
    }

    void HandlePIN::PIN_UninstallISR()
    {
        gpio_uninstall_isr_service();
    }

    esp_err_t HandlePIN::PIN_AddHandlerISR(gpio_isr_t isr_handl)
    {
        return gpio_isr_handler_add(_PIN,isr_handl,nullptr);
    }

    esp_err_t HandlePIN::PIN_SetOutputPower(gpio_drive_cap_t strength)
    {
        return gpio_set_drive_capability(_PIN,strength);
    }

    esp_err_t HandlePIN::PIN_EasyINTR(gpio_isr_t isr_func)
    {
        esp_err_t Error = ESP_OK;
        Error |= gpio_set_intr_type(_PIN,GPIO_INTR_ANYEDGE);
        Error |= gpio_intr_enable(_PIN);
        Error |= gpio_install_isr_service(ESP_INTR_FLAG_LEVEL1);
        Error |= gpio_isr_handler_add(_PIN, isr_func, nullptr);
        return Error; 
    }
}