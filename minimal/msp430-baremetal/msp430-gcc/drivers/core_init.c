#include "core_init.h"

void vHardwareCoreSetup(void)
{
    // Disable Watchdog
    WDTCTL = WDTPW | WDTHOLD;
    
    // Power System Initialization
    SetVCore(3);                            // Set VCORE to highest possible voltage
    
    // Clock Initialization
    
    // Enable Crystal Pins
    P5SEL |= BIT2+BIT3;                     // Port select XT2
    P5SEL |= BIT4+BIT5;                     // Port select XT1

    __bis_SR_register(SCG0);                // Disable FLL
    
    // Turn on Crystals
    UCSCTL6 &= ~XT2OFF;                     // Turn XT2 On
    UCSCTL6 |= XCAP_3;                      // Internal Load Caps
    UCSCTL6 &= ~XT1OFF;                     // Turn XT1 On
    
    // Enable SMCLK out for Debug
    //P2DIR |= BIT2;
    //P2SEL |= BIT2;

    // Setup FLL
    UCSCTL3 = SELREF__XT2CLK +              // FLL REF from XT2CLK
        FLLREFDIV__1;                       // No division for FLLREF
    
    UCSCTL2 = FLLN2 + FLLN0;                // FLL Multiplier 5+1
    
    // Setup DCO
    UCSCTL1 = DCORSEL_6;                    // DCO Range Selection to include 24MHz

    __bic_SR_register(SCG0);                // Reenable FLL

    // Wait for everything to stabilize
    do
    {
        UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
                                            // Clear Individual Fault Flags
        SFRIFG1 &= ~OFIFG;                  // Clear Fault Flags
    }while (SFRIFG1 & OFIFG);               // While Oscillator Fault Flag
    
    // Select Clock Sources
    UCSCTL4 = SELA__XT1CLK +                // ACLK from XT1CLK
        SELS__DCOCLK +                      // SMCLK from DCOCLK 
        SELM__DCOCLK;                       // MCLK from XT2CLK

    // Apply dividers if needed
    UCSCTL5 = DIVM__1 +                     // No MCLK Division ( 24 MHz )
        DIVS__2 +                           // SMCLK/2 for Debug ( 12 MHz )
        DIVA__1 +                           // No ACLK Division ( 32.768 KHz )
        DIVPA__1;                           // No ACLK Pin Division
    
    // Access Control on the Clocks
    UCSCTL8 = SMCLKREQEN + MCLKREQEN + ACLKREQEN;
    
    return;
}
