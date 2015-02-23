USB-API Notes                 {#usbapinotes}
=============

Minor changes are made to the code to enable better integration. An attempt 
is made to track these changes and the rationale for each here. However, it
is entirely possible that some changes will be missed from this list. Use a 
diff/meld against the upstream version to see all changes.

Upstream version : `4_20_00`

Changes from upstream:
----------------------

- Changed function declarations to avoid compiler warnings. In all cases, empty 
  argument list is changed to `void`. This may or may not be correct. Functions which
  are not specifically checked for correctness in relation to this change are marked
  as `(unverified)`.(`-Wstrict-prototypes`)
    
    - In `USB_Common/usb.c`: 
        * Line 122, decl of `MscResetData()` (unverified)
        * Line 282, decl of `CdcResetData()` (unverified)
        * Line 283, decl of `HidResetData()` (unverified)
        * Line 284, decl of `PHDCResetData()` (unverified)

    - In `USB_Common/usb.h`:        
        * Line 341, decl of `USB_enable()` (unverified) 
        * Line 373, decl of `USB_getEnabledEvents()` (unverified) 
        * Line 378, decl of `USB_connect()` (unverified) 
        * Line 383, decl of `USB_disconnect()` (unverified) 
        * Line 388, decl of `USB_reset()` (unverified) .
        * Line 406, decl of `USB_forceRemoteWakeup()` (unverified) 
        * Line 411, decl of `USB_connectionInfo()` (unverified) .
        * Line 416, decl of `USB_connectionState()` (unverified) 
        * Line 434, decl of `USB_handleClockEvent()` (unverified) 
        * Line 440, decl of `USB_handleVbusOnEvent()` (unverified) 
        * Line 446, decl of `USB_handleVbusOffEvent()` (unverified) 
        * Line 452, decl of `USB_handleResetEvent()` (unverified) 
        * Line 459, decl of `USB_handleSuspendEvent()` (unverified) .
        * Line 466, decl of `USB_handleResumeEvent()` (unverified) 
        * Line 473, decl of `USB_handleEnumCompleteEvent()` (unverified) 
        
    - In `USB_CDC_API/UsbCdc.c`: 
        * Line 116, decl in def of `CdcResetData()` (unverified) .
    
    - In `USB_CDC_API/UsbCdc.h`:     
        * Line 190, decl of `USBCDC_setupDMA_Bridge()` (unverified)
    
    - In `USB_HID_API/UsbHid.c`: 
        * Line 110, decl in def of `HidResetData()` (unverified)
    
    - In `USB_MSC_API/UsbMsc.h`:    
        * Line 62, decl of `MSCToHostFromBuffer()` (unverified)
        * Line 63, decl of `MSCFromHostToBuffer()` (unverified)
        * Line 65, decl of `USBMSC_getState()` (unverified)

- Fixed dangling cond blocks:
    
    - From `USB_MSC_API/UsbMscReq.c`, at bottom of the file cond to endcond. 
    
- Removed deprecated `USB_Common/types.h` entirely.

- Added prototypes for functions which don't have them. (`-Wmissing-prototypes`)

    - for `USB_getVersion()` in `USB_Common/usb.c` to `USB_Common/usb.h`
    - for `memcpyV()` in `USB_Common/usbdma.c` to `USB_Common/usbdma.c`
    - for `memcpyDMA()` in `USB_Common/usbdma.c` to `USB_Common/usbdma.c`
    - for `USB_initMemcpy()` in `USB_Common/usbdma.c` to `USB_Common/usbdma.c`
    - for `CdcResetData()` in `USB_CDC_API/UsbCdc.c` to `USB_CDC_API/UsbCdc.c` (private)
    - for `CdcToHostFromBuffer()` in `USB_CDC_API/UsbCdc.c` to `USB_CDC_API/UsbCdc.c` (private)
    - for `CopyUsbToBuff()` in `USB_CDC_API/UsbCdc.c` to `USB_CDC_API/UsbCdc.c` (private)
    - for `CdcToBufferFromHost()` in `USB_CDC_API/UsbCdc.c` to `USB_CDC_API/UsbCdc.c` (private)
    - for `CdcIsReceiveInProgress()` in `USB_CDC_API/UsbCdc.c` to `USB_CDC_API/UsbCdc.c` (private)
    - for `HidResetData()` in `USB_HID_API/UsbHid.c` to `USB_HID_API/UsbHid.c` (private)
    - for `HidToHostFromBuffer()` in `USB_HID_API/UsbHid.c` to `USB_HID_API/UsbHid.c` (private)
    - for `HidToBufferFromHost()` in `USB_HID_API/UsbHid.c` to `USB_HID_API/UsbHid.c` (private)
    - for `HidIsReceiveInProgress()` in `USB_HID_API/UsbHid.c` to `USB_HID_API/UsbHid.c` (private)
    - for `iUsbInterruptHandler()` in `USB_config/UsbIsr.c` to `USB_config/UsbIsr.c` (ISR)
    
- Commented out variable declarations where obviously unused. (`Wunused-variable`)
        
    - `volatite uint16_t i`, at Line 1151 of `USB_Common/usb.c`
    
- Variables that may be uninitialized are forced to some default value. This
  'default' value is generally meaningless and the variables if not already 
  initialized or not overwritten later would represent catastrophic failure 
  anyway. `(-Wmaybe-unintialized)`
    
    - `USB_Common/usb.c`, 
        - `freq` in `USB_determineFreq()` to 0

- Corrected argument names in doxygen comments to match declaration:
    
    - In `USB_app/usbConstructs.c`, line 501, `intfnum` to `intfNum`
    - In `USB_app/usbConstructs.c`, line 424, `intfnum` to `intfNum`
    - In `USB_app/usbConstructs.c`, line 339, `intfnum` to `intfNum`
    - In `USB_app/usbConstructs.c`, line 271, `intfnum` to `intfNum`
    - In `USB_app/usbConstructs.c`, line 194, `intfnum` to `intfNum`
    - In `USB_app/usbConstructs.c`, line 111, `intfnum` to `intfNum`
    
- Extra paranthesis added around conditions that include an assignment (=) 
  instead of a comparison. These have not been verified to be assignments. 
  Upstream implemented an assignment, we just mark it as so. `(-Wparantheses)`
    
    - In `USB_app/usbConstructs.c`, line 303, `bytesInBuf`
    - In `USB_app/usbConstructs.c`, line 533, `bytesInBuf`
    
- In `USB_API/USB_Common/usbdma.c`, lines 98 and 99, `(uint32_t)source` and 
  `(uint32_t)dest` cause compiler warnings (`Wpointer-to-int-cast`). Warnings
  cleared by two-stage cast. `(uint32_t)(uintptr_t)source`.
            
Outstanding Problems:
---------------------

- In `USB_API/USB_Common/usb.c`, line 70, `define __no_init` redefines 
  `__no_init` defined by `/opt/ti/gcc/include/in430.h` to be 
  `__attribute__ ((section (".noinit")))`. Why this define is cleared for 
  this file, which continues to use `__no_init` in various definitions, is 
  unknown. Replaced all occurences of `__no_init ` with `__no_init_usb ` in 
  all files under `USB_API` for now.

- Added extra conditional include blocks to temporarily fix strange comments:

    - In `USB_MSC_API/UsbMscScsi.c`, line 1485, function prototype does not 
      specify arguments but argument documented.
      

- In `USB_API/USB_Common/usb.c`, in `usbDecodeAndProcessUsbRequest()`, 
  line 1892. `-Wcast-align` should be fixed.
  