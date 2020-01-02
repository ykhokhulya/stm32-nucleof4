cmake_minimum_required(VERSION 2.8)

project(07-discovery_board_f3)
enable_language(ASM)

find_package(CMSIS REQUIRED)
find_package(STM32HAL COMPONENTS gpio i2c pcd spi uart REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${STM32Cube_DIR}/Drivers/BSP/STM32F3-Discovery
    ${STM32Cube_DIR}/Middlewares/ST/STM32_USB_Device_Library/Core/Inc
    ${STM32Cube_DIR}/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc
    ${STM32Cube_DIR}/Drivers/BSP/Components/l3gd20
    ${STM32Cube_DIR}/Drivers/BSP/Components/lsm303dlhc
    ${CMSIS_INCLUDE_DIRS}
    ${STM32HAL_INCLUDE_DIR})

file(GLOB_RECURSE PROJECT_SOURCES *.c)
file(GLOB_RECURSE DISCOVERY_BSP_SOURCES
    ${STM32Cube_DIR}/Drivers/BSP/STM32F3-Discovery/*.c)
list(APPEND PROJECT_SOURCES ${DISCOVERY_BSP_SOURCES})
list(APPEND PROJECT_SOURCES
    ${STM32Cube_DIR}/Drivers/BSP/Components/l3gd20/l3gd20.c
    ${STM32Cube_DIR}/Drivers/BSP/Components/lsm303dlhc/lsm303dlhc.c
    ${STM32Cube_DIR}/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Src/usbd_hid.c
    ${STM32Cube_DIR}/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c
    ${STM32Cube_DIR}/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c
    ${STM32Cube_DIR}/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c)

add_executable(
    ${PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${CMSIS_SOURCES}
    ${STM32HAL_SOURCES})

stm32_set_target_properties(${PROJECT_NAME})
stm32_add_hex_bin_targets(${PROJECT_NAME})
stm32_print_size_of_targets(${PROJECT_NAME})
