CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Basic MSP430 drivers

# Backchannel UART driver
ADD_PLATFORM_LIBRARY(bc_uart STATIC "" bc_uart.c bc_uart.h)
ADD_PLATFORM_LIBRARY(core_init STATIC "" core_init.c core_init.h)
ADD_PLATFORM_LIBRARY(tick_timer STATIC "" tick_timer.c tick_timer.h)


# TI Libraries
ADD_PLATFORM_LIBRARY(HAL_PMM STATIC "" HAL_PMM.c HAL_PMM.h)



