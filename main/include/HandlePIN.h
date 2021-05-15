/**
 * @file HandlePIN.h 
 * @author Vincent de Man
 * @brief Header for HandlePIN class (.h).
 * @version 0.1
 * @date 2021-05-15
 * @details Header file for handlePIN class.
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef HandlePIN_H
#define HandlePIN_H

#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_intr_alloc.h"

extern "C"
{

    class HandlePIN
    {
    public:
        
        HandlePIN(const gpio_num_t PIN, gpio_mode_t MODE = GPIO_MODE_OUTPUT, gpio_pull_mode_t PULL = GPIO_PULLDOWN_ONLY);
        ~HandlePIN();
        [[nodiscard]] esp_err_t PIN_Initialize();
        [[nodiscard]] int PIN_GetLevel();
        esp_err_t PIN_High();
        esp_err_t PIN_Low();
        esp_err_t PIN_Toggle();
        inline void PIN_ChangeMode(const gpio_mode_t MODE);
        inline void PIN_ChangePullMode(const gpio_pull_mode_t PULL);
        inline void PIN_ChangeInt(const gpio_int_type_t INTR);
        inline gpio_num_t PIN_GetNum() const;
        inline gpio_mode_t PIN_GetMode();
        inline gpio_pull_mode_t PIN_GetPull();
        inline gpio_int_type_t PIN_GetIntr();
        esp_err_t PIN_Reset();
        esp_err_t PIN_SetINTR();
        esp_err_t PIN_EnableINTR();
        esp_err_t PIN_DisableINTR();
        esp_err_t PIN_InstallISR(int flags = ESP_INTR_FLAG_LEVEL1);
        void PIN_UninstallISR();
        esp_err_t PIN_AddHandlerISR(gpio_isr_t isr_handl);
        esp_err_t PIN_SetOutputPower(gpio_drive_cap_t strength);
        esp_err_t PIN_EasyINTR(gpio_isr_t isr_func);
        

    private : 
        const gpio_num_t _PIN;
        gpio_mode_t _MODE;
        gpio_pull_mode_t _PULL;
        gpio_int_type_t _INTR = GPIO_INTR_DISABLE;

        enum highlow
        {
            LOW = 0,
            HIGH = 1
        };
        constexpr static const char *TAG = "PIN";
    };
}

#endif