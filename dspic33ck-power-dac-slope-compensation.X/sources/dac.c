
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
 * File: dac.c 
 * Author: A14426
 * Comments:  source file of dac.h header file
 * Revision history: Initial Release
 */

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types

#include "config/demo.h"
#include "dac.h"

/* Declaration of user-defined DAC instance */
volatile struct P33C_DAC_INSTANCE_s* my_dac; // User-specified DAC instance

/* Declaration of generic DAC module data object */
volatile struct P33C_DAC_MODULE_s* my_dac_module;     // DAC module object 

volatile uint16_t DAC_Initialize(void){

    volatile uint16_t retval=1;

    my_dac_module = p33c_DacModule_GetHandle();
    retval &= p33c_DacModule_ConfigWrite(dacModuleConfigClear);

    my_dac_module->DacModuleCtrl1L.bits.CLKSEL =0b10;  // DAC Clock Source: AFPLLO  
    my_dac_module->DacModuleCtrl2H.bits.SSTIME = (DAC_SSTIME & 0x0FFF); // Transition Mode Duration (default 0x55 = 340ns @ 500 MHz)     
    my_dac_module->DacModuleCtrl2L.bits.TMODTIME = (DAC_TMODTIME  & 0x03FF); // Time from Start of Transition Mode until Steady-State Filter is Enabled (default 0x8A = 552ns @ 500 MHz)

    my_dac = p33c_DacInstance__GetHandle(DAC_INSTANCE); //// user-defined DAC 1 object 
    retval &= p33c_DacInstance_ConfigWrite(DAC_INSTANCE, dacConfigClear);

    #if defined (__MA330048_dsPIC33CK_DPPIM__)
    my_dac->SLPxCONL.bits.SLPSTOPA = 0b0001; // Slope Stop A Signal: PWM1 Trigger 2
    #elif defined (__MA330049_dsPIC33CH_DPPIM__)
    pg->SLPxCONL.bits.SLPSTOPA = 0b0101;  // Slope Stop A Signal: PWM1 Trigger 2
    #endif

    my_dac->SLPxCONL.bits.SLPSTOPB = 0b0000; // Slope Stop B Signal: 0=none, 1=comparator 1, 2=comparator 2, etc.
    my_dac->SLPxCONL.bits.SLPSTRT  = 0b0001; // Slope Start Signal: PWM1 Trigger 1
//    my_dac_instance->SLPxCONL.bits.SLPSTOPA = 0b0001; // Slope Stop A Signal: PWM1 Trigger 2
    my_dac->SLPxDAT.value  = SLP_SLEW_RATE_1; // Slope Ramp Rate Value Slope 
    
    my_dac->DACxDATH.value = DACOUT_VALUE_HIGH_1;   // specifies the high DACx data value
    my_dac->DACxDATL.value = 0;  // In Hysteretic mode, Slope Generator mode and Triangle mode, this register specifies the low data value and/or limit for the DACx module
    my_dac->DACxCONH.value = DAC_LEADING_EDGE_BLNK; // Set DAC Leading Edge Blanking period
    
    my_dac->SLPxCONH.bits.SLOPEN = 1;      // Slope Function: Enable slope function; 

    return(retval);

}

volatile uint16_t DAC_Enable(void) {
    
    volatile uint16_t retval=1;
    
    my_dac->DACxCONL.bits.DACOEN = 1;      // Output DAC voltage to DACOUT1 pin
    my_dac->DACxCONL.bits.DACEN = 1;       // enable DAC module
    my_dac_module->DacModuleCtrl1L.bits.DACON = 1;  // enable DAC

    retval = (my_dac->DACxCONL.bits.DACEN & my_dac_module->DacModuleCtrl1L.bits.DACON);
    
    return(retval);
}

volatile uint16_t DAC_Disable(void) {
    
    volatile uint16_t retval=1;
    
    my_dac->DACxCONL.bits.DACEN = 0;       // enable DAC module
    my_dac_module->DacModuleCtrl1L.bits.DACON = 0;  // enable DAC

    retval = (1 - (my_dac->DACxCONL.bits.DACEN & my_dac_module->DacModuleCtrl1L.bits.DACON));
    
    return(retval);
}

