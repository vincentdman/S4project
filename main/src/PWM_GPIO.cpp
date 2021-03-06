/**
 * @file PWM_GPIO.cpp
 * @author Vincent de Man
 * @brief Basic gpio PWM dirver class (.cpp)
 * @version 1.1
 * @date 2021-03-24
 * @copyright Copyright (cpp) 2021
 * @class PWM_GPIO Advanced class to give PWM functionality to a object.
 * @details Implementation of the pwm gpio class. It uses the inherited handle gpio functions. 
 *
 */
#include "PWM_GPIO.h"


extern "C"
{
    /**
     * @brief Construct a new pwm gpio::pwm gpio object
     * 
     * @details default constructor for PWM_GPIO object
     */
    PWM_GPIO::PWM_GPIO()
    {
    }

    /**
     * @brief Construct a new pwm gpio::pwm gpio object and initializes the given parameter
     * 
     * @param PIN The pin that gets initialized at creation of the object.
     * 
     * @details Constructor to also initialize the pin
     */
    PWM_GPIO::PWM_GPIO(const gpio_num_t PIN)
    {
        PWM_Initialize(PIN);  
    }

    /**
     * @brief function to set the PWM frequency 
     * 
     * @param Frequency The desired PWM Frequency
     * @param PIN The designated pin 
     * 
     * @details function to set the pwm frequency on a given pin. The user can put in a pin that gets affected. 
     * 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     */
    esp_err_t PWM_GPIO::SetFrequency(const uint32_t Frequency, const gpio_num_t PIN)
    {
        ledc_timer.freq_hz = Frequency;
        return PWM_Initialize(PIN);
    }

    /**
     * @brief function to update the Channel configuration
     * 
     * @details Function to update the configuration that is stored in ledc_channel variable inside the class. 
     * 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     */
    esp_err_t PWM_GPIO::UpdateChannelConfig()
    {
        return ledc_channel_config(&ledc_channel);
    }

    /**
     * @brief function to update the Timer Configuration
     * 
     * @details Function to update the configuration that is stored in ledc_timer variable inside the class. 
     * 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     */
    esp_err_t PWM_GPIO::UpdateTimerConfig()
    {
        return ledc_timer_config(&ledc_timer);
    }

    /**
     * @brief function to set the duty cycle of the pwm signal
     * 
     * @param duty The desired duty cycle 0-100
     * @param PIN The designated pin 
     * @param Channel The affected pwm channel
     * 
     * @details Function to set the duty cycle on a pwm output signal. This function takes a int from 0-100 and sets the duty cycle accordingly.
     * 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     */
    esp_err_t PWM_GPIO::SetDuty(int duty, const gpio_num_t PIN, const ledc_channel_t Channel)
    {
        ESP_LOGD(TAG,"Set the duty for PIN%d to %d%% pwm output.\n",PIN,duty);         
        duty = duty * 8191 / 100;
        ledc_channel.channel = Channel;
        ledc_channel.duty = duty;
        return PWM_Initialize(PIN);
    }

    /**
     * @brief function to initialize the given pin for pwm signal output
     * 
     * @param PIN The pin that gets initialized
     * 
     * @details This function takes a pin in as input and configures it to output a pwm signal. The duty cycle will be at default 0 
     * 
     * @return esp_err_t value is ESP_OK when there is no error and when there is a error it has the corresponding error as value.
     */
    esp_err_t PWM_GPIO::PWM_Initialize(const gpio_num_t PIN)
    {
        esp_err_t Error = ESP_OK; 
        ledc_channel.gpio_num = PIN;
        Error |= ledc_timer_config(&ledc_timer);
        Error |= ledc_channel_config(&ledc_channel);
        ESP_LOGD(TAG,"Initialize PIN%d for pwm output.\n",PIN);   
        return Error; 
    }
}