cmake_minimum_required(VERSION 2.8)

project(06-usb_device)
enable_language(ASM)

find_package(CMSIS REQUIRED)
find_package(STM32HAL COMPONENTS gpio uart pcd REQUIRED)

set(STM32USBD_DEV_DIR ${STM32Cube_DIR}/Middlewares/ST/STM32_USB_Device_Library)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${STM32USBD_DEV_DIR}/Class/CustomHID/Inc
    ${STM32USBD_DEV_DIR}/Core/Inc
    ${CMSIS_INCLUDE_DIRS}
    ${STM32HAL_INCLUDE_DIR})

file(GLOB_RECURSE PROJECT_SOURCES *.c)
list(APPEND PROJECT_SOURCES
    ${STM32USBD_DEV_DIR}/Class/CustomHID/Src/usbd_customhid.c
    ${STM32USBD_DEV_DIR}/Core/Src/usbd_core.c
    ${STM32USBD_DEV_DIR}/Core/Src/usbd_ctlreq.c
    ${STM32USBD_DEV_DIR}/Core/Src/usbd_ioreq.c)

add_executable(
    ${PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${CMSIS_SOURCES}
    ${STM32HAL_SOURCES})

stm32_set_target_properties(${PROJECT_NAME})
stm32_add_hex_bin_targets(${PROJECT_NAME})
stm32_print_size_of_targets(${PROJECT_NAME})
