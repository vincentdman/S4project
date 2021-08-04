/**
 * @file HandleHID.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <driver/gpio.h>

#include "esp_log.h"
#include "esp_err.h"

extern "C" {

    class HandleHID 
    {
        public:
            HandleHID(const gpio_num_t Output);
        
        private: 

    };



}
