CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(application_SRCS main.c)
LIST(APPEND deps "bc_uart core_init tick_timer HAL_PMM")
ADD_PLATFORM_EXECUTABLE(firmware ${deps} ${application_SRCS})
