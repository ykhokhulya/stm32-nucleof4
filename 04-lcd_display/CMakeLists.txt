cmake_minimum_required(VERSION 2.8)

project(04-lcd_display)
enable_language(ASM)

find_package(CMSIS REQUIRED)
find_package(STM32HAL COMPONENTS gpio uart REQUIRED)

file(GLOB_RECURSE PROJECT_SOURCES *.c)

add_executable(
    ${PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${CMSIS_SOURCES}
    ${STM32HAL_SOURCES})

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE ${CMSIS_INCLUDE_DIRS}
    PRIVATE ${STM32HAL_INCLUDE_DIR})

stm32_set_target_properties(${PROJECT_NAME})
stm32_add_hex_bin_targets(${PROJECT_NAME})
stm32_print_size_of_targets(${PROJECT_NAME})
