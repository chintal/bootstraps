
FIND_PACKAGE("msp430-driverlib" REQUIRED)
FIND_PACKAGE("bytebuf" REQUIRED)
FIND_PACKAGE("printf" REQUIRED)

ADD_PLATFORM_LIBRARY(hal-uc-core STATIC "msp430-driverlib" core_impl.c)
ADD_PLATFORM_LIBRARY(hal-uc-gpio STATIC "msp430-driverlib" gpio_impl.c)
ADD_PLATFORM_LIBRARY(hal-uc-uart STATIC "msp430-driverlib bytebuf printf" uart_impl.c uart_handlers.c)
