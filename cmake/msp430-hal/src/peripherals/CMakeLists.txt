

ADD_SUBDIRECTORY(driverlib)

ADD_MSP430_LIBRARY(hal-uc-core STATIC "driverlib" core_impl.c)
ADD_MSP430_LIBRARY(hal-uc-gpio STATIC "driverlib" gpio_impl.c)
ADD_MSP430_LIBRARY(hal-uc-uart STATIC "driverlib bytebuf" uart_impl.c)
