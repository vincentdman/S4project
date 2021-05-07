/**
 * @file PWM_GPIO.h
 * @author Vincent de Man
 * @brief Header file for PWM GPIO dirver (.h).
 * @version 1.1
 * @date 2021-03-24
 * @details header file for the pwm gpio functions. Includes all functions used to use the gpio.
 * @copyright Copyright (cpp) 2021
 * 
 */
#ifndef PWM_GPIO_h
#define PWM_GPIO_h

#include "esp_err.h"
#include "esp_system.h"
#include <driver/gpio.h>
#include "driver/ledc.h"

extern "C"
{
    class PWM_GPIO
    {
    public:
        PWM_GPIO(gpio_num_t);
        PWM_GPIO();
        void PWM_Initialize(gpio_num_t);
        void SetDuty(int, gpio_num_t, ledc_channel_t);
        void SetFrequency(uint32_t, gpio_num_t);
        void UpdateTimerConfig();
        void UpdateChannelConfig();

    private:
        ledc_timer_config_t ledc_timer =
            {
                .speed_mode = LEDC_LOW_SPEED_MODE,
                .duty_resolution = LEDC_TIMER_13_BIT,
                .timer_num = LEDC_TIMER_1,
                .freq_hz = 5000,
                .clk_cfg = LEDC_AUTO_CLK};

        ledc_channel_config_t ledc_channel =
            {
                .gpio_num = GPIO_NUM_26,
                .speed_mode = LEDC_LOW_SPEED_MODE,
                .channel = LEDC_CHANNEL_0,
                .intr_type = LEDC_INTR_DISABLE,
                .timer_sel = LEDC_TIMER_1,
                .duty = 0, //max 8191
                .hpoint = 0

        };
    };
}

#endif