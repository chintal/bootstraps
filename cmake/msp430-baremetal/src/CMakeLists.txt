CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(msp430-gcc-primitives C)

SET(SUPPORTED_DEVICES "msp430f5529;msp430f5521" 
	CACHE STRING "Supported Target Devices")
	
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/drivers ${INCLUDE_DIRECTORIES})
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/applications ${INCLUDE_DIRECTORIES})

ADD_SUBDIRECTORY(drivers)
ADD_SUBDIRECTORY(application)

INSTALL(SCRIPT default-install.cmake)
