cmake_minimum_required(VERSION 2.8)
project(Stm32Learning)

set(STM32Cube_DIR ${PROJECT_SOURCE_DIR}/stm32-fw-cube/F4)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/stm32-cmake/cmake)

add_subdirectory(00-user_button)
add_subdirectory(01-printf_to_uart)
add_subdirectory(02-rtc_date_time)
add_subdirectory(03-rtc_alarm)
add_subdirectory(04-lcd_display)
