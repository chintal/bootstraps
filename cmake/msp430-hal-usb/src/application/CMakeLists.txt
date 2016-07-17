

# Added to ensure USB ISR gets linked in. A cleaner solution should be found.
SET(EXTRA_SOURCES ${CMAKE_SOURCE_DIR}/peripherals/USB_config/UsbIsr.c)
SET(application_SRCS main.c ${EXTRA_SOURCES})
LIST(APPEND deps "hal-uc-uart hal-uc-gpio hal-uc-core prbs usb-api usb-config usb-app bc-iface-usb")
ADD_PLATFORM_EXECUTABLE(firmware ${deps} ${application_SRCS})
