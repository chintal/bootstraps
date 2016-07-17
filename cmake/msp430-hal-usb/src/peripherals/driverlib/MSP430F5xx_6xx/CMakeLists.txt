CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
cmake_policy(SET CMP0007 NEW)

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR} ${INCLUDE_DIRECTORIES}")

FOREACH(device ${SUPPORTED_DEVICES})
    IF(device MATCHES "msp430f(5|6)[a-z|0-9]*$")
        LIST(APPEND RESULTV ${device})
    ENDIF(device MATCHES "msp430f(5|6)[a-z|0-9]*$")
ENDFOREACH(device ${SUPPORTED_DEVICES})

SET(SUPPORTED_DEVICES ${RESULTV})

IF(SUPPORTED_DEVICES)
ADD_PLATFORM_LIBRARY(driverlib STATIC "" 	adc10_a.c 
					adc12_a.c
					aes.c
					battbak.c
					comp_b.c
					crc.c
					dac12_a.c
					dma.c
					eusci_a_spi.c
					eusci_a_uart.c
					eusci_b_i2c.c
					eusci_b_spi.c
					eusci_i2c.c
					eusci_spi.c
					eusci_uart.c
					flashctl.c
					gpio.c
					ldopwr.c
					mpy32.c
					pmap.c
					pmm.c
					ram.c
					ref.c
					rtc_a.c
					rtc_b.c
					rtc_c.c
					sd24_b.c
					sfr.c
					sysctl.c
					tec.c
					timer_a.c
					timer_b.c
					timer_d.c
					tlv.c
					ucs.c
					usci_a_spi.c
					usci_a_uart.c
					usci_b_i2c.c
					usci_b_spi.c
					usci_i2c.c
					usci_spi.c
					usci_uart.c
					wdt_a.c)
ENDIF(SUPPORTED_DEVICES)