
FIND_PACKAGE("prbs" REQUIRED)

SET(application_SRCS main.c)
LIST(APPEND deps "hal-uc-uart hal-uc-gpio hal-uc-core prbs")
ADD_PLATFORM_EXECUTABLE(firmware ${deps} ${application_SRCS})
