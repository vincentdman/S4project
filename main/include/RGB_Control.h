/**
 * @file RGB_Control.h
 * @author Vincent de Man
 * @brief Header file for RGB control (.h)
 * @version 0.1
 * @date 2021-03-24
 * 
 * @copyright Copyright (c) 2021
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
        RGB_Control(gpio_num_t, gpio_num_t, gpio_num_t);
        void SetRed(void);
        void SetGreen(void);
        void SetBlue(void);
        void SetPurple(void);
        void SetYellow(void);
        void SetCyan(void);
        void SetWhite(void);
        void SetRGB(int, int, int);
        void SetRGB_Red(int);
        void SetRGB_Green(int);
        void SetRGB_Blue(int);
        void ChangeChannelRed(ledc_channel_t);
        void ChangeChannelGreen(ledc_channel_t);
        void ChangeChannelBlue(ledc_channel_t);

    private:
        gpio_num_t Red;
        gpio_num_t Green;
        gpio_num_t Blue;

        ledc_channel_t RedChannel = LEDC_CHANNEL_0;
        ledc_channel_t GreenChannel = LEDC_CHANNEL_1;
        ledc_channel_t BlueChannel = LEDC_CHANNEL_2;
    };
}

#endif