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

extern"C"
{

HandleSPI::HandleSPI(spi_host_device_t Host = SPI1_HOST)
    : SPI_Host(Host)
{
    SPI_Initialize();
}
esp_err_t HandleSPI::SPI_Initialize()
{
    esp_err_t Error = ESP_OK;
    Error = spi_bus_initialize(SPI_Host, &SPI_Config, SPI_DMA_CH_AUTO);
    
    return Error;
}


}