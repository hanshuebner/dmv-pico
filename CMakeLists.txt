cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(dmv_pico C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()
add_executable(dmv_pico
        dmv_pico.c
        dmv_bus.h
        dmv_2651.c
        signetics_2651_uart.h
)
pico_enable_stdio_usb(dmv_pico 1)
pico_enable_stdio_uart(dmv_pico 0)
pico_add_extra_outputs(dmv_pico)
target_link_libraries(dmv_pico pico_stdlib pico_multicore)