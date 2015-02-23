

# Project Structure

# Project Structure {#structure}

Lorem Ipsum

## USB API Integration and Usage Notes {#usbhal}

Due to the complexity of the USB implentation, the HAL is handled differently 
for USB compared to the other peripherals. The HAL only has minimal control 
over the interface, and most of the details are left to the underlying 
implementation. Most configuration details are not taken from the PUM and 
are instead hardcoded into the implementation. 
 
When porting to a different board/uc/product, care must be taken. The needed
configuration data should go into the underlying implementation. As such, it
is recommended that as far as possible, the predefined USB configurations 
should be used as far as possible. A separate protocol can be built on top of
the USB layer. 

All the USB API files are compiled by themselves to form a linkable library.
`peripherals/USB_config` and `peripherals/USB_app` are the folders where 
application specific files go. These folders are also given to `USB_API` as
include directories during compile. Together with the USB HAL, this forms the
core of USB specific code.

The HAL is kept minimal and doesn't provide many directly usable functions. The 
vast majority of the HAL simply just proxy to the underlying implementation 
functions. Instead, specific USB interface types are implemented as `subsystems` 
which use the more basic functions from the HAL. Ideally, subsystems should not 
directly call the USB_API functions to maintain portability. 

Additionally, various other pieces of code 
required to handle USB are scattered through the source tree. A detailed account
of the full USB footprint should be added here to make the documentation usable.
As a general case, most code present outside the standard folders are : 

- Event handlers, which are typically called by the USB interrupt
- Deferred Execution functions, which act on flags set by the interrupt and handlers

The application specific files should be treated as 'standard' USB configurations
for use with products. Multiple products using the same configuration then use the 
same underlying USB implementation, `.INF` files, and basic drivers, hopefully 
simplifying development, installation, and support. Actual product identification 
can be done outside of USB. Thus, the USB related code and hardware should roughly 
relate to OSI model layers 1-3.


### Device-side OSI layers ###

These interfaces don't really conform to the nature of OSI model networks. However,
for the sake of identifying the elements which make up the full interface, we use 
the OSI model as a familiar starting point to indicate the general function of the 
various parts of the implementation.

- Layer 1 : USB hardware upto the uC USB peripheral
- Layers 2, 3 : USB peripheral, `USB_API`, and `hal_uc_usb`
- Layer 4 : `USB_API` and subsystem trigger functions
- Layer 5 : USB subsystem related event handlers and inits
- Layers 6, 7 : USB subsystem libraries


### USB Device Configurations ###

The present configuration is named `Class 1 Quazar USB Configuration`, and the 
devices should enumerate as `Class 1 Quazar USB Device`. This configuration is
a Composite Device, containing the following interfaces : 

- Interface 0 : CDC : `Payload Data Stream`
- Interface 1 : CDC : `Control Data Stream`     
- Interface 2 : CDC : `Backchannel Interface`   
- Interface 3 : HID : `RT Control Stream`

### Interface 0 : CDC : `Payload Data Stream` ###

### Interface 1 : CDC : `Control Data Stream` ###

### Interface 2 : CDC : `Backchannel Interface` ###

**Subsystem** : `subsystem/bc_iface.h`

**Related Libraries** 
    
- `lib/bytebuf.h`
- `lib/printf.h`

**Application Level Triggers** 

- `bcusb_send_trigger()`

**Application Level Handlers and Flags** 

- `bcif_tx_inprogress`
- `bcif_handle_txdone`
- `board_iface_USBCDC_txdhandler()`

### Interface 3 : HID : `RT Control Stream` ###