cmake_minimum_required(VERSION 2.8)

project(blinky-hal)
enable_language(ASM)

list(APPEND CMAKE_MODULE_PATH ../stm32-cmake/cmake)

find_package(CMSIS REQUIRED)
find_package(STM32HAL COMPONENTS gpio REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMSIS_INCLUDE_DIRS}
    ${STM32HAL_INCLUDE_DIR})

file(GLOB_RECURSE PROJECT_SOURCES *.c)

add_executable(
    ${CMAKE_PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${CMSIS_SOURCES}
    ${STM32HAL_SOURCES})

stm32_set_target_properties(${CMAKE_PROJECT_NAME})
stm32_add_hex_bin_targets(${CMAKE_PROJECT_NAME})
stm32_print_size_of_targets(${CMAKE_PROJECT_NAME})
