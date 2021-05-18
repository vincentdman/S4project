/**
 * @file RGB_Control.h
 * @author Vincent de Man
 * @brief Header file for RGB control (.h).
 * @version 1.1
 * @date 2021-03-24
 * @details Header file for rgb control class. includes all functions tp use a rgb led object.
 * @copyright Copyright (cpp) 2021
 * 
 */
#ifndef RGB_CONTROL_h
#define RGB_CONTROL_h
#include "HandleGPIO.h"
#include "PWM_GPIO.h"

extern "C"
{
    class RGB_Control : private HandleGPIO, private PWM_GPIO
    {
    public:
        RGB_Control(const gpio_num_t _Red, const gpio_num_t _Green, const gpio_num_t _Blue);
        esp_err_t SetRed(void);
        esp_err_t SetOff(void);
        esp_err_t SetGreen(void);
        esp_err_t SetBlue(void);
        esp_err_t SetPurple(void);
        esp_err_t SetYellow(void);
        esp_err_t SetCyan(void);
        esp_err_t SetWhite(void);
        esp_err_t SetRGB(int, int, int);
        esp_err_t SetRGB_Red(int);
        esp_err_t SetRGB_Green(int);
        esp_err_t SetRGB_Blue(int);
        void ChangeChannelRed(const ledc_channel_t);
        void ChangeChannelGreen(const ledc_channel_t);
        void ChangeChannelBlue(const ledc_channel_t);

    private:
        const gpio_num_t Red;
        const gpio_num_t Green;
        const gpio_num_t Blue;

        ledc_channel_t RedChannel = LEDC_CHANNEL_0;
        ledc_channel_t GreenChannel = LEDC_CHANNEL_1;
        ledc_channel_t BlueChannel = LEDC_CHANNEL_2;

        constexpr static const char* TAG = "RGB";    

    };
}

#endif