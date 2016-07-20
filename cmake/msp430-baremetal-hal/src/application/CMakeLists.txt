
FIND_PACKAGE("prbs" REQUIRED)
FIND_PACKAGE("ucdm" REQUIRED)
FIND_PACKAGE("modbus" REQUIRED)

SET(application_SRCS main.c)
LIST(APPEND deps "hal-uc-uart hal-uc-gpio hal-uc-core prbs ucdm modbus")
ADD_PLATFORM_EXECUTABLE(firmware ${deps} ${application_SRCS})
