cmake_minimum_required(VERSION 2.8)
project(Stm32Learning)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/stm32-cmake/cmake)

if (${STM32_CHIP} STREQUAL STM32F446RE)
    set(STM32Cube_DIR ${PROJECT_SOURCE_DIR}/stm32-fw-cube/F4)

    add_subdirectory(00-user_button)
    add_subdirectory(01-printf_to_uart)
    add_subdirectory(02-rtc_date_time)
    add_subdirectory(03-rtc_alarm)
    add_subdirectory(04-lcd_display)
    add_subdirectory(05-temp_sensor)

elseif(${STM32_CHIP} STREQUAL STM32F303VCT6)
    set(STM32Cube_DIR ${PROJECT_SOURCE_DIR}/stm32-fw-cube/F3)

    add_subdirectory(06-usb_device)
    add_subdirectory(07-discovery_board_f3)

endif()
