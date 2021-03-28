/**
 * @file PWM_GPIO.cpp
 * @author Vincent de Man
 * @brief Basic gpio PWM dirver class (.cpp)
 * @version 0.1
 * @date 2021-03-24
 * @copyright Copyright (c) 2021
 * @class PWM_GPIO Advanced class to give PWM functionality to a object
 * 
 */
#include "driver/ledc.h"
#include "esp_err.h"
#include "esp_system.h"
#include <driver/gpio.h>
#include "PWM_GPIO.h"

extern "C"
{
    /**
     * @brief Construct a new pwm gpio::pwm gpio object
     * 
     */
    PWM_GPIO::PWM_GPIO()
    {
    }
    /**
     * @brief Construct a new pwm gpio::pwm gpio object and initializes the given parameter
     * 
     * @param PIN The designated pin 
     */
    PWM_GPIO::PWM_GPIO(gpio_num_t PIN)
    {
        PWM_Initialize(PIN);
    }
    /**
     * @brief function to set the PWM frequency 
     * 
     * @param Frequency The desired PWM Frequency
     * @param PIN The designated pin 
     */
    void PWM_GPIO::SetFrequency(uint32_t Frequency, gpio_num_t PIN)
    {
        ledc_timer.freq_hz = Frequency;
        PWM_Initialize(PIN);
    }
    /**
     * @brief function to update the Channel configuration
     * 
     */
    void PWM_GPIO::UpdateCannelConfig()
    {
        ledc_channel_config(&ledc_channel);
    }
    /**
     * @brief function to update the Timer Configuration
     * 
     */
    void PWM_GPIO::UpdateTimerConfig()
    {
        ledc_timer_config(&ledc_timer);
    }
    /**
     * @brief function to set the duty cycle of the pwm signal
     * 
     * @param duty The desired duty cycle
     * @param PIN The designated pin 
     * @param Channel The affected pwm channel
     */
    void PWM_GPIO::SetDuty(int duty, gpio_num_t PIN, ledc_channel_t Channel)
    {
        //duty in range 0 to 8191
        duty = duty * 8191 / 100;
        ledc_channel.channel = Channel;
        ledc_channel.duty = duty;
        PWM_Initialize(PIN);
    }
    /**
     * @brief function to initialize the given pin for pwm signal output
     * 
     * @param PIN The pin that gets initialized
     */
    void PWM_GPIO::PWM_Initialize(gpio_num_t PIN)
    {
        ledc_channel.gpio_num = PIN;
        ledc_timer_config(&ledc_timer);
        ledc_channel_config(&ledc_channel);
    }
}