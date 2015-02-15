

SET(application_SRCS main.c)
LIST(APPEND deps "hal-uc-uart hal-uc-gpio hal-uc-core prbs")
ADD_MSP430_EXECUTABLE(firmware ${deps} ${application_SRCS})
