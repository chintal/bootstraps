
DriverLib Notes                 {#driverlibnotes}
===============

Minor changes are made to the code to enable better integration. An attempt 
is made to track these changes and the rationale for each here. However, it
is entirely possible that some changes will be missed from this list. Use a 
diff/meld against the upstream version to see all changes.

Upstream version : `1_97_00_19`

Changes from upstream:
----------------------

- `IFNDEF` preprocessor condition added around `NDEBUG` to avoid compiler warnings:
    - `MSP430F5xx_6xx/inc/hw_regaccess.h`
	
- Variables that may be uninitialized are forced to some default value. This
  'default' value is generally meaningless and the variables if not already 
  initialized or not overwritten later would represent catastrophic failure 
  anyway. `(-Wmaybe-unintialized)`
    - `MSP430F5xx_6xx/ucs.c`, 
        - `CLKFrequency` in `privateUCSComputeCLKFrequency()` to 0
        - `Fref_value` in `privateUCSSourceClockFromDCO()` to 0

- Extra paranthesis added around conditions that include an assignment (=) 
  instead of a comparison. These have not been verified to be assignments. 
  Upstream implemented an assignment, we just mark it as so. `(-Wparantheses)`
    - `MSP430F5xx_6xx/usci_a_uart.c`, at lines 190, 196 (locMask)
    - `MSP430F5xx_6xx/usci_uart.c`, at lines 190, 195 (locMask)
    
- Added snippet to help `msp430.h` resolve in kdevelop's parser.
    - `/opt/ti/gcc/include/msp430.h`
    
- Escaped `\#` in comment to avoid `Doxygen` warnings.
    - `MSP430F5xx_6xx/timer_a.h`, in `Timer_A_getCounterValue()`
    - `MSP430F5xx_6xx/timer_b.h`, in `Timer_B_getCounterValue()`

- Added closing tags in comment to avoid `Doxygen` warnings.
    - `MSP430F5xx_6xx/usci_b_spi.h`, `</b>` in `USCI_B_SPI_receiveData()` 
      at line 304.
    
Outstanding Problems:
---------------------

- In `MSP430F5xx_6xx/tlv.c`, in `TLV_getInfo()`, line 80. `-Wcast-align` should be fixed.
