cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_SDK_PATH /home/pi/pico/pico-sdk)
include(~/pico/pico-sdk/external/pico_sdk_import.cmake)
include(pico_sdk_import.cmake)

project(test_project C CXX)

pico_sdk_init()

add_executable(test user_funcs.c console.c test.c)

pico_enable_stdio_uart(test 1)

target_link_libraries(test pico_stdlib)

pico_add_extra_outputs(test)
