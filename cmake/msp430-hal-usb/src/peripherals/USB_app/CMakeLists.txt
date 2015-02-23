
ADD_MSP430_LIBRARY(usb-app STATIC "driverlib usb-api board-funcs" usbConstructs.c
                                                                  usbEventHandling.c)
