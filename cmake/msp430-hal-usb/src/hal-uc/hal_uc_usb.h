
/* 
   Copyright 2015 Quazar Technologies Pvt. Ltd.
   Copyright 2015 Chintalagiri Shashank
    
   This file is part of
   Embedded bootstraps : hal-uC
   
   This library is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>. 
*/


/**
 * @file hal_uc_usb.h
 * @brief HAL for USB interface
 *
 * This file is the hardware abstraction layer for uC USB interfaces. Due to 
 * the complexity of the USB implentation, this layer is handled differently for
 * USB compared to the other peripherals. The HAL only has minimal control over
 * the interface, and most of the details are left to the underlying 
 * implementation. Most configuration details are not taken from the PUM and 
 * are instead hardcoded into the implementation. 
 * 
 * When porting to a different board/uc/product, care must be taken. The needed
 * configuration data should go into the underlying implementation. As such, it
 * is recommended that as far as possible, the predefined USB configurations 
 * should be used as far as possible. A separate protocol can be built on top of
 * the USB layer. 
 * 
 * The function names in this file are all prefixed by `hal_` since they shadow 
 * the function names in the implementation provided by the manufacturer. The 
 * only role of the implementation in `usb_impl.h` and `usb_impl.c` is to translate 
 * these function names to the names in the underlying manufacturer implementation.
 * 
 * The intent is to try and provide a unified, even if feature-incomplete, HAL 
 * interface to handle multiple USB device libraries across uC families. 
 * 
 * The application can use the underlying functions directly as well, for the cost 
 * of reduction in portablility.
 *
 * The following function sets are currently not included within the HAL and are 
 * considered part of the underlying implementation, and should usually not be 
 * accessed directly by the application. Implementation of these functions is also
 * not intended to be application specific within the framework created here, and 
 * changing the implementation of these functions may have other uninteded 
 * consequences if the HAL is being used. 
 *   - All USB Event Handlers are in `peripherals/USB_app/usbEventHandling.c`
 *   - Implementations of all underlying functions are referenced in 
 *     `peripherals/usb_impl.h` and for msp430 are implemented within 
 *     `peripherials/USB_API/`
 * 
 * @see [USB API Integration and Usage Notes](@ref usbhal)
 * 
 * @see usb_impl.h 
 * @see usb_impl.c
 */

#ifndef HAL_UC_USB_H
#define HAL_UC_USB_H

#include "uc_pum.h"

// Set up the API

#if PUM_HAS_USB == 1


/**
 * @name USB Management API Functions
 * 
 * All shadow MSP430 USB-API functions. 
 */
/**@{*/ 
/**
 * \brief Initialize USB and connect if possible.
 */
static inline void hal_usb_setup(void);

/**
 * \brief Enable the USB module. 
 * 
 * Needed only if USB is being disabled
 * intermittently. Otherwise, the contents of this function
 * should also be included in `usb_setup()`.
 */
static inline void hal_usb_enable(void);

/**
 * \brief Disable the USB module. 
 * 
 * Needed only if USB is being disabled
 * intermittently. Otherwise, this function is never needed.
 */
static inline void hal_usb_disable(void);

/**
 * \brief Connect to host. 
 * 
 * Needed only if USB is being disabled
 * intermittently. Otherwise, the contents of this function
 * should also be included in `usb_setup()`.
 */
static inline void hal_usb_connect(void);

/**
 * \brief Disconnect from host. 
 * 
 * Needed only if USB is being disabled
 * intermittently. Otherwise, this function is never needed.
 */
static inline void hal_usb_disconnect(void);
/**@}*/ 

/**
 * @name USB Connection Status API Functions
 * 
 * For status parameters not supported here, call the underlying 
 * API directly and review if this API will benefit from those 
 * parameters being added to the minimal set.
 * 
 * usb_impl.h should define the following status values : 
 *  - `HUSB_ST_DISCONNECTED`  : USB Host is not connected
 *  - `HUSB_ST_NOTENUMERATED` : USB Host is connected but not enumerated
 *  - `HUSB_ST_ENUMERATING` : USB Enumeration in progress
 *  - `HUSB_ST_ACTIVE` : USB is ready for use
 *  - `HUSB_ST_SUSPENDED`: Host has placed the device in suspend
 *  - `HUSB_ST_NOENUM_SUSPENDED` : Device suspended before enumeration.
 */
/**@{*/ 

/**
 * \brief Get the current status of the USB subsystem.
 * \returns Status as specified as one of the allowed status defines.
 *          
 */
static inline uint8_t hal_usb_status(void);

/**
 * \brief Get the current status of a specific USB CDC TX interface.
 * 
 * \warning This function for MSP430 USB API will report USB CDC TX ready even 
 * before the last transaction is completed and the txdone handlers are called. 
 * 
 * \param intfNum Interface Number
 * \returns 0 if CDC TX is in use or otherwise not available, 1 if CDC TX is
 *          ready to recieve additional data from a user buffer.
 */
static inline uint8_t hal_usb_cdcif_txready(uint8_t intfNum);

/**
 * \brief Get number of unhandled bytes of a specific USB CDC RX interface.
 * \param intfNum Interface Number
 * \returns Number of unhandled bytes waiting in the interface API buffer.
 */
static inline uint8_t hal_usb_cdcif_rxwaiting(uint8_t intfNum);
/**@}*/


/**
 * @name USB CDC Interface API Functions
 *      
 */
/**@{*/ 

/**
 * \brief Discard all unhandled bytes of a specific USB CDC RX interface.
 * \param intfNum Interface Number
 */
static inline void hal_usb_cdcif_discardrxb(uint8_t intfNum);
/**@}*/

/**
 * @name USB API Event Handling Functions
 *      
 * A minimal set of critical events are to be handled per-application. The 
 * functions listed here are to be called via the underlying API when 
 * certain events occur. Every USB implementation must ensure that these 
 * functions are called, and every USB project must implement these 
 * functions to ensure USB compliance.
 * 
 * Since these functions are board dependent, these functions declarations
 * should be part of `bsp/board_pum.h` and the definitions must be available 
 * by link-time.
 */
/**@{*/ 

/**
 * \brief React to USB suspend.
 * 
 * This function should be called by the underlying USB suspend event handler
 * implementation before switching the MCU to it's low power state. 
 * 
 * If the device is bus-powered, the implementation of this function must shut 
 * off everything on the board to reduce power consumption to zero or near zero.
 * 
 * By default, this implementation of the USB HAL will call a function called
 * `board_suspend()` whose declaration should be included by `board_pum.h`.
 */
static inline void hal_usb_event_suspend(void);

/**
 * \brief React to USB resume.
 * 
 * This function should be called by the underlying USB suspend event handler
 * implementation before switching the MCU back into it's normal state. 
 * 
 * If the device is bus-powered, the implementation of this function must turn
 * back on everything it turned off for the suspend.
 * 
 * By default, this implementation of the USB HAL will call a function called
 * `board_resume()` whose declaration should be included by `board_pum.h`.
 */
static inline void hal_usb_event_resume(void);

/**
 * \brief React to USB reset.
 * 
 * This function should be called by the underlying USB reset event handler
 * implementation.
 * 
 * This function probably isn't needed, according to the USB_API docs. However, 
 * it it provided in case USB reset cause desynchronization of a higher level
 * protocol. This function can be used as a hook to reset the protocols to a 
 * known state. Ideally, the protocols should be inherently resilient to USB 
 * reset. 
 * 
 * By default, this implementation of the USB HAL will call a function called
 * `board_iface_reset()` whose declaration should be included by `board_pum.h`.
 */
static inline void hal_usb_event_reset(void);

/**
 * \brief React to CDC TX Complete.
 * 
 * This function should be called by the underlying USB reset event handler
 * implementation.
 * 
 * By default, this implementation of the USB HAL will call a function called
 * `board_iface_USBCDC_txdhandler()` whose declaration should be included by 
 * `board_pum.h`.
 */
static inline void hal_usb_event_CDC_txdone(uint8_t intfNum);


/**@}*/


#endif

// Set up the implentation
#include "usb_impl.h"

#endif

