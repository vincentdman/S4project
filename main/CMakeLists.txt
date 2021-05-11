idf_component_register(
    SRCS "main.cpp" "src/HandleGPIO.cpp" "src/RGB_Control.cpp" "src/PWM_GPIO.cpp" "src/LCD_Control.cpp" "src/HandleI2C.cpp" "src/HandleBMP180.cpp"
    INCLUDE_DIRS "include"
)

target_compile_definitions(${COMPONENT_LIB} PUBLIC "-DLOG_LOCAL_LEVEL=ESP_LOG_VERBOSE")
