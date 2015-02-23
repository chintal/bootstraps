

ADD_MSP430_LIBRARY(usb-api STATIC "driverlib" USB_Common/usb.c
                                              USB_Common/usbdma.c
                                              USB_CDC_API/UsbCdc.c
                                              USB_HID_API/UsbHid.c
                                              USB_HID_API/UsbHidReq.c
                                              USB_MSC_API/UsbMscReq.c
                                              USB_MSC_API/UsbMscScsi.c
                                              USB_MSC_API/UsbMscStateMachine.c
                                              USB_PHDC_API/UsbPHDC.c)

