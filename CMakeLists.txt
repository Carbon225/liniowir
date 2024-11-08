cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(liniowir C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(main
    ${CMAKE_CURRENT_LIST_DIR}/src/main.c
    ${CMAKE_CURRENT_LIST_DIR}/src/motors.c
    ${CMAKE_CURRENT_LIST_DIR}/src/sensors.c
    ${CMAKE_CURRENT_LIST_DIR}/src/motoron/Motoron.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/motoron/motoron_c.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/bootsel_button.c
    ${CMAKE_CURRENT_LIST_DIR}/src/fusion/mahony.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/mpu9250/mpu9250.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/imu.cpp
)
target_link_libraries(main pico_stdlib hardware_watchdog hardware_pwm hardware_gpio hardware_i2c)
pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)
pico_add_extra_outputs(main)
