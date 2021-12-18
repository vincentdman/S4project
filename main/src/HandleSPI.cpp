/**
 * @file HandleSPI.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-12-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "HandleSPI.h"

extern "C"
{

    HandleSPI::HandleSPI(spi_host_device_t Host = SPI1_HOST)
        : SPI_Host(Host)
    {
        SPI_Initialize();
        SPI_AddBus();
    }
    esp_err_t HandleSPI::SPI_Initialize()
    {
        ESP_LOGI(TAG, "Initialized SPI!");
        return spi_bus_initialize(SPI_Host, &SPI_Config, SPI_DMA_CH_AUTO);
    }

    esp_err_t HandleSPI::SPI_AddBus()
    {
        return spi_bus_add_device(SPI_Host, &SPI_DeviceConfig, &SPI_DeviceHandle);
    }

    HandleSPI::~HandleSPI()
    {
        spi_bus_remove_device(SPI_DeviceHandle);
    }
}
