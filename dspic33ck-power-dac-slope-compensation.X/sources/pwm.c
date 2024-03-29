/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File: pwc.c 
 * Author: A14426
 * Comments: Initializes the switching frequency PWM
 * Revision history: 
 *  1.0 Initial version
 *  1.1 cleaned up and simplified version
 */

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types

#include "config/demo.h"
#include "pwm.h"

/* Declaration of user-defined PWM instance */
volatile struct P33C_PWM_GENERATOR_s* my_pg1 ;    // user-defined PWM generator 1 object 


volatile uint16_t PWM_Initialize(void) {
    
    volatile uint16_t retval=1;

    // Default PWM Initialization for 500 MHz input clock from AUX PLL
    retval &= p33c_PwmModule_Initialize();

    // Capture handle to the desired PWM generator 
    my_pg1 = p33c_PwmGenerator_GetHandle(PWM_GENERATOR);
   
    // Reset PGx SFRs to RESET conditions
    retval &= p33c_PwmGenerator_ConfigWrite(PWM_GENERATOR, pgConfigClear);
  
    
    // Set individual PWM generator configuration for PG1
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    // PGxCONL: PWM GENERATOR x CONTROL REGISTER LOW
    my_pg1->PGxCONL.bits.CLKSEL = 0b01; // PWM Generator uses Master clock selected by the MCLKSEL[1:0] (PCLKCON[1:0]) control bits
    my_pg1->PGxCONL.bits.MODSEL = 0b000; // Independent Edge PWM mode
    my_pg1->PGxCONL.bits.HREN   = 1; // PWM Generator x operates in High-Resolution mode
    
    // PGxCONH: PWM GENERATOR x CONTROL REGISTER HIGH
    my_pg1->PGxCONH.bits.UPDMOD = 0b00; // SOC update: Data registers at start of next PWM cycle if UPDREQ = 1
    my_pg1->PGxCONH.bits.TRGMOD = 0b0; // PWM Generator operates in Single Trigger mode
    my_pg1->PGxCONH.bits.SOCS   = 0b0000; // SOCS[3:0]: Start-of-Cycle Selection: Local EOC ? PWM Generator is self-triggered
    
    // PGxIOCONL: PWM GENERATOR x I/O CONTROL REGISTER LOW
    my_pg1->PGxIOCONL.bits.OSYNC = 0b00;  // User output overrides via the OVRENH/L and OVRDAT[1:0] 
                                          // bits are synchronized to the local PWM time base (next Start-of-Cycle)
    my_pg1->PGxIOCONL.bits.OVRDAT = 0b00; // Both PWM outputs are LOW in override mode
    my_pg1->PGxIOCONL.bits.OVRENL = 1; // OVRDAT0 provides data for output on the PWMxL pin
    my_pg1->PGxIOCONL.bits.OVRENH = 1; // OVRDAT1 provides data for output on the PWMxH pin
        
    // PGxEVTL: PWM GENERATOR EVENT REGISTER LOW
    my_pg1->PGxEVTL.bits.PGTRGSEL = 0b000; // No PWM Generator Trigger Output
    my_pg1->PGxEVTL.bits.ADTR1EN2 = 1;     // PG1TRIGB register compare event is enabled  as trigger source for Start of Slope Start Signal
    
    /* PGxEVTH: PWM GENERATOR  EVENT REGISTER HIGH */
    my_pg1->PGxEVTH.bits.ADTR2EN3 = 1;     // PG1TRIGC register compare event is enabled as trigger source for Slope Stop A Signal
    
    // PGxIOCONH: PWM GENERATOR x I/O CONTROL REGISTER HIGH
    my_pg1->PGxIOCONH.bits.PMOD = 0b00; // PWM Generator outputs operate in Complementary mode
    
    // Set PWM signal generation timing of this generator 
    my_pg1->PGxPER.value = PWM_PERIOD;          // Set switching frequency
    my_pg1->PGxDC.value  = PWM_DUTY_CYCLE;      // Set initial duty cycle
    my_pg1->PGxDTH.value = PWM_DEAD_TIME_RE;    // Set rising edge dead time
    my_pg1->PGxDTL.value = PWM_DEAD_TIME_FE;    // Set falling edge dead time     
    
    // Set PWM signal generation trigger output timing
    my_pg1->PGxTRIGB.value = SLP_TRIG_START;    // Set ramp start trigger location
    my_pg1->PGxTRIGC.value = SLP_TRIG_STOP;     // Set ramp stop trigger location
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // PLEASE NOTE:
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Digital Power Plug-In Modules may have additional circuits dedicated to 
    // specific functions connected to some of their device pins. The following  
    // pre-compiler instructions disabling certain PWM outputs interfering with  
    // analog filter circuits and are therefore not available on the hardware
    // you may be using.
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    #if defined (__MA330048_dsPIC33CK_DPPIM__)

    // On dsPIC33CK DP PIM (MA330048) PWM generator output PWM7L is shared
    // with the on-board push button of the Digital Power Development
    // Board (DM330029). The PWM7L output signal will get filtered and
    // distorted by the switch de-bounce capacitor and is therefore 
    // being turned off here.
    
    if(PWM_GENERATOR == 7) 
    {
        my_pg1->PGxIOCONL.bits.OVRENL = 1;
        my_pg1->PGxIOCONH.bits.PENL   = 0;
    }
    
    #elif defined (__MA330049_dsPIC33CH_DPPIM__)

    // On dsPIC33CH DP PIM (MA330049) PWM generator output PWM2L is shared
    // with the on-board push button of the Digital Power Development
    // Board (DM330029). The PWM7L output signal will get filtered and
    // distorted by the switch de-bounce capacitor and is therefore 
    // being turned off here.

    if(MOTHER_PWM_GENERATOR == 2) 
    {
        my_pg1.pgHandle->PGxIOCONL.bits.OVRENL = 1;
        my_pg1.pgHandle->PGxIOCONH.bits.PENL = 0;
    }
    
    #endif

    // Check return value
    retval &= (bool)(my_pg1->PGxCONL.bits.ON) &&         // Check if PWM generator is turned on
                   (!my_pg1->PGxIOCONL.bits.OVRENH);  
    
    return(retval); // Return 1=success, 0=failure
    
}

volatile uint16_t PWM_Enable(void) {

    volatile uint16_t retval=1;

    // Enable PWM generators with outputs DISABLED
    retval &= p33c_PwmGenerator_Enable(my_pg1); 
    
    Nop(); // Place breakpoint to review PWM configuration
    Nop(); // using the Watch Window
    Nop();
    
    // Enable PWM generator outputs 
    retval &= p33c_PwmGenerator_Resume(my_pg1); 
    
    return(retval); // Return 1=success, 0=failure

}

// ________________________
// end of file
