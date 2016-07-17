

ADD_SUBDIRECTORY(driverlib)
ADD_SUBDIRECTORY(USB_API)
ADD_SUBDIRECTORY(USB_app)
ADD_SUBDIRECTORY(USB_config)

ADD_PLATFORM_LIBRARY(hal-uc-core STATIC "driverlib" core_impl.c)
ADD_PLATFORM_LIBRARY(hal-uc-gpio STATIC "driverlib" gpio_impl.c)
ADD_PLATFORM_LIBRARY(hal-uc-uart STATIC "driverlib bytebuf printf" uart_impl.c)
