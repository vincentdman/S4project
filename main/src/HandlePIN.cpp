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

extern "C"
{

    /**
     * @brief Construct a new HandlePIN::HandlePIN object.
     * 
     * @param PIN The selected GPIO pin.
     * @param MODE The gpio mode.
     * @param PULL The pull mode.
     * 
     * @details Constructor to create a new handlePIN object to handle single pins.
     */
    HandlePIN::HandlePIN(const gpio_num_t PIN, gpio_mode_t MODE, gpio_pull_mode_t PULL)
        : _PIN(PIN), _MODE(MODE), _PULL(PULL)
    {
        if (!GPIO_IS_VALID_GPIO(_PIN))
        {
            ESP_LOGE(TAG, "ERROR pin isn't correct\n");
        }
    }

    /**
     * @brief Destroy the HandlePIN::HandlePIN object
     * @details Destructor uninstalls everything from the interrupt service routine. 
     */
    HandlePIN::~HandlePIN()
    {
        gpio_uninstall_isr_service();
        gpio_isr_handler_remove(_PIN);
    }

    /**
     * @brief Function to initialize the gpio pin.
     * 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     * 
     * @details Function to initialize the pin with the values given in the constructor. 
     */
    esp_err_t HandlePIN::PIN_Initialize()
    {
        esp_err_t Error = ESP_OK;
        Error |= gpio_set_direction(_PIN, _MODE);
        Error |= gpio_set_pull_mode(_PIN, _PULL);
        return Error;
    }

    /**
     * @brief Function to set the GPIO pin high.
     * 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     * 
     * @details Function to set the GPIO pin to high output. Only works when output mode is selected. 
     */
    esp_err_t HandlePIN::PIN_High()
    {
        esp_err_t Error = ESP_OK;
        Error |= gpio_set_level(_PIN, HIGH);
        return Error;
    }

    /**
     * @brief Function to set the pin to low
     * 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     * 
     * @details Function to set the GPIO output to low.
     */
    esp_err_t HandlePIN::PIN_Low()
    {
        esp_err_t Error = ESP_OK;
        Error |= gpio_set_level(_PIN, LOW);
        return Error;
    }

    /**
     * @brief Function to get the level on the gpio pin.
     * 
     * @return int 1 means high 0 means low voltage level on the pin.
     * 
     * @details Function to get the level on the gpio pin. Only works for input gpio pins.
     */
    int HandlePIN::PIN_GetLevel()
    {
        return gpio_get_level(_PIN);
    }

    /**
     * @brief Function to change the gpio mode for the pin. Dont forget to reset and initialize again. 
     * 
     * @param MODE The new gpio mode for the pin.
     * 
     * @details Function to change the gpio mode for the pin. Dont forget to reset and initialize again. 
     */
    void HandlePIN::PIN_ChangeMode(const gpio_mode_t MODE)
    {
        _MODE = MODE;
    }

    /**
     * @brief Function to change the pull mode of the PIN. Dont forget to reset and initialize again. 
     * 
     * @param PULL The new pull mode for the pin.
     * 
     * @details Function to change the pull mode of the PIN. Dont forget to reset and initialize again. 
     */
    void HandlePIN::PIN_ChangePullMode(const gpio_pull_mode_t PULL)
    {
        _PULL = PULL;
    }

    /**
     * @brief Change the interrupt type of the pin. Dont forget to reset and initialize again.
     * 
     * @param INTR The new interrupt type.
     * 
     * @details Function to change the interrupt type of the pin. Dont forget to reset and initialize again.
     */
    void HandlePIN::PIN_ChangeInt(const gpio_int_type_t INTR)
    {
        _INTR = INTR;
    }
    
    /**
     * @brief Function to get the current pin number.
     * 
     * @return gpio_num_t The PIN number.
     * 
     * @details Function to get the current pin numer gpio_num_t.
     */
    gpio_num_t HandlePIN::PIN_GetNum() const
    {
        return _PIN;
    }

    /**
     * @brief Function to get the pinmode.
     * 
     * @return gpio_mode_t The pinmode.
     * 
     * @details Function to get the current pinmode.
     */
    gpio_mode_t HandlePIN::PIN_GetMode()
    {
        return _MODE;
    }

    /**
     * @brief Function to get the pullmode.
     * 
     * @return gpio_pull_mode_t The pullmode.
     * 
     * @details Function to get the currently used gpio pullmode.
     */
    gpio_pull_mode_t HandlePIN::PIN_GetPull()
    {
        return _PULL;
    }

    /**
     * @brief Function to get the interrupt type.
     * 
     * @return gpio_int_type_t The interrupt type.
     * 
     * @details Function that returns the currently used interrupt type.
     */
    gpio_int_type_t HandlePIN::PIN_GetIntr()
    {
        return _INTR;
    }

    /**
     * @brief Function to reset the pin.
     * 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     * 
     * @details Function to reset the currently used gpio pin.
     */
    esp_err_t HandlePIN::PIN_Reset()
    {
        return gpio_reset_pin(_PIN);
    }

    /**
     * @brief Function to set the intr type.
     * 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     * 
     * @details Function to set the currently selected interrupt type to the pin.
     */
    esp_err_t HandlePIN::PIN_SetINTR()
    {
        return gpio_set_intr_type(_PIN, _INTR);
    }

    /**
     * @brief Function to enebale interrupts on the pin.
     * 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     * 
     * @details Function to enable interrupts on the currently used pin.
     */
    esp_err_t HandlePIN::PIN_EnableINTR()
    {
        return gpio_intr_enable(_PIN);
    }

    /**
     * @brief Function to disable interrupts on the pin.
     * 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     * 
     * @details Function to disable interrupts on the currently selected pin. 
     */
    esp_err_t HandlePIN::PIN_DisableINTR()
    {
        return gpio_intr_disable(_PIN);
    }

    /**
     * @brief Function to install the ISR service.
     * 
     * @param flags The ISR flags.
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     * 
     * @details Function to install the ISR more info about the flags can be found in esp_intr_alloc.h.
     */
    esp_err_t HandlePIN::PIN_InstallISR(int flags)
    {
        return gpio_install_isr_service(flags);
    }

    /**
     * @brief Function to uninstall the ISR.
     * 
     * @details Function to uninstall the interrupt service routine.
     */
    void HandlePIN::PIN_UninstallISR()
    {
        gpio_uninstall_isr_service();
    }

    /**
     * @brief Function to add a isr handler to the pin.
     * 
     * @param isr_handl The Handler function.
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     * 
     * @details Function to add a user function to handle the interrupt.
     */
    esp_err_t HandlePIN::PIN_AddHandlerISR(gpio_isr_t isr_handl)
    {
        return gpio_isr_handler_add(_PIN, isr_handl, nullptr);
    }

    /**
     * @brief Function to set the output power of the pin.
     * 
     * @param strength The output strenght. 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     * 
     * @details Function to set the output power of the pin. 
     */
    esp_err_t HandlePIN::PIN_SetOutputPower(gpio_drive_cap_t strength)
    {
        return gpio_set_drive_capability(_PIN, strength);
    }

    /**
     * @brief Function to easily init the isr.
     * 
     * @param isr_func The user function that will be called on interrupt. 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     * 
     * @details Function to easily init the interrupt on the pin with default settings.
     */
    esp_err_t HandlePIN::PIN_EasyINTR(gpio_isr_t isr_func)
    {
        esp_err_t Error = ESP_OK;
        
        if(_MODE != GPIO_MODE_INPUT){
            ESP_LOGE(TAG,"Please make sure PIN is selected as input");
            return ESP_FAIL;
        }
        Error |= gpio_install_isr_service(ESP_INTR_FLAG_EDGE);
        Error |= gpio_isr_handler_add(_PIN, isr_func, nullptr);
        Error |= gpio_set_intr_type(_PIN, GPIO_INTR_ANYEDGE);
        Error |= gpio_intr_enable(_PIN);
        return Error;
    }
}