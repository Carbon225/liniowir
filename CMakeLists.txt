cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
include(FreeRTOS_Kernel_import.cmake)
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

    ${CMAKE_CURRENT_LIST_DIR}/src/network/access_point/picow_access_point.c
    ${CMAKE_CURRENT_LIST_DIR}/src/network/access_point/dhcpserver/dhcpserver.c
    ${CMAKE_CURRENT_LIST_DIR}/src/network/access_point/dnsserver/dnsserver.c

    ${CMAKE_CURRENT_LIST_DIR}/src/network/httpd/picow_httpd.c
)

target_include_directories(main PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/config
    ${CMAKE_CURRENT_LIST_DIR}/src/include
)

target_link_libraries(main
    pico_stdlib
    pico_multicore

    hardware_watchdog
    hardware_pwm
    hardware_gpio
    hardware_i2c

    pico_cyw43_arch_lwip_sys_freertos
    pico_lwip_http
    pico_lwip_mdns
    pico_freertos_httpd_content

    FreeRTOS-Kernel
    FreeRTOS-Kernel-Static
    FreeRTOS-Kernel-Heap4
)

target_compile_options(main PUBLIC
    ### Gnu/Clang C Options
    $<$<COMPILE_LANG_AND_ID:C,GNU>:-fdiagnostics-color=always>
    $<$<COMPILE_LANG_AND_ID:C,Clang>:-fcolor-diagnostics>

    $<$<COMPILE_LANG_AND_ID:C,Clang,GNU>:-Wall>
    $<$<COMPILE_LANG_AND_ID:C,Clang,GNU>:-Wextra>
    $<$<COMPILE_LANG_AND_ID:C,Clang,GNU>:-Werror>
    $<$<COMPILE_LANG_AND_ID:C,Clang>:-Weverything>

    -Wno-psabi
)

pico_add_library(pico_freertos_httpd_content NOFLAG)
pico_set_lwip_httpd_content(pico_freertos_httpd_content INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/network/httpd/content/404.html
    ${CMAKE_CURRENT_LIST_DIR}/src/network/httpd/content/index.shtml
    ${CMAKE_CURRENT_LIST_DIR}/src/network/httpd/content/test.shtml
)

pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)
pico_add_extra_outputs(main)
