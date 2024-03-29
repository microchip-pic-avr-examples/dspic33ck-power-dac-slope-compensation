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

// Include standard header files
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types

#include "p33c_dac.h"

/* @@p33c_DacModule_Dispose
 * ********************************************************************************
 * Summary:
 *     Resets all DAC Module registers to their RESET default values
 * 
 * Parameters:
 *     (none)
 * 
 * Returns:
 *     0 = failure, disposing DAC module was not successful
 *     1 = success, disposing DAC module was successful
 * 
 * Description:
 *     This function clears all DAC module registers to their
 *     default values set when the device comes out of RESET. 
 * 
 *     Default configuration:
 *         - all outputs are set to logic functions
 *         - all analog functions are disabled
 *         - all pull-up and pull-down resistors are disabled
 *         - all DACs are operating in push-pull mode (open drain disabled)
 *         - all DACs are configured as input with their signal level HIGH
 * 
 * ********************************************************************************/

volatile uint16_t p33c_DacModule_Dispose(void)
{
    volatile uint16_t retval=1;
    
    retval = p33c_DacModule_ConfigWrite(dacModuleConfigClear);
    
    return(retval);
}

/* @@p33c_DacModule_ConfigRead
 * ********************************************************************************
 * Summary:
 *     Read the current configuration from the DAC module base registers
 * 
 * Parameters:
 *     (none)
 * 
 * Returns:
 *     0 = failure, reading DAC module was not successful (returns NULL)
 *     n = success, reading DAC module was successful (returns 16-bit wide pointer)
 * 
 * Description:
 *     This function reads all registers with their current configuration into
 *     a data structure of type P33C_DAC_MODULE_s. Users can read and 
 *     verify or modify the configuration to write it back to the DAC module  
 *     registers.
 * 
 * ********************************************************************************/

volatile struct P33C_DAC_MODULE_s p33c_DacModule_ConfigRead(void)
{
    volatile struct P33C_DAC_MODULE_s* dac;

    // Set pointer to memory address of desired DAC instance
    dac = (volatile struct P33C_DAC_MODULE_s*)((volatile uint8_t*) &DACCTRL1L);

    return(*dac);
    
}

/* @@p33c_DacInstance_ConfigWrite
 * ********************************************************************************
 * Summary:
 *     Writes a user-defined configuration to the DAC module base registers
 * 
 * Parameters:
 *     (none)
 * 
 * Returns:
 *     0 = failure, writing DAC module was not successful
 *     1 = success, writing DAC module was successful
 * 
 * Description:
 *     This function writes a user-defined DAC module configuration of type 
 *     P33C_DAC_MODULE_s to the DAC module base registers. The 
 *     individual register configurations have to be set in user-code 
 *     before calling this function. To simplify the configuration process
 *     of standard functions, this driver provides templates, which can be 
 *     loaded and written directly.
 * 
 * ********************************************************************************/

volatile uint16_t p33c_DacModule_ConfigWrite(
        volatile struct P33C_DAC_MODULE_s dacModuleConfig
)
{
    volatile uint16_t retval=1;
    volatile struct P33C_DAC_MODULE_s* dac;    

    // Set pointer to memory address of the DAC module base registers
    dac = (volatile struct P33C_DAC_MODULE_s*)((volatile uint8_t*) &DACCTRL1L);
    *dac = dacModuleConfig;
    
    return(retval);
    
}


/* ============================================================================== */
/* ============================================================================== */
/* ============================================================================== */


/* @@p33c_DacInstance_Dispose
 * ********************************************************************************
 * Summary:
 *     Resets all DAC Instance registers to their RESET default values
 * 
 * Parameters:
 *     (none)
 * 
 * Returns:
 *     0 = failure, disposing DAC instance was not successful
 *     1 = success, disposing DAC instance was successful
 * 
 * Description:
 *     This function clears all DAC instance registers to their
 *     default values set when the device comes out of RESET. 
 * 
 *     Default configuration:
 *         - all outputs are set to logic functions
 *         - all analog functions are disabled
 *         - all pull-up and pull-down resistors are disabled
 *         - all DACs are operating in push-pull mode (open drain disabled)
 *         - all DACs are configured as input with their signal level HIGH
 * 
 * ********************************************************************************/

volatile uint16_t p33c_DacInstance_Dispose(volatile uint16_t dacInstance)
{
    volatile uint16_t retval=1;
    
    retval = p33c_DacInstance_ConfigWrite(dacInstance, dacConfigClear);
    
    return(retval);
}

/* @@p33c_DacInstance_ConfigRead
 * ********************************************************************************
 * Summary:
 *     Read the current configuration from the DAC instance registers
 * 
 * Parameters:
 *     (none)
 * 
 * Returns:
 *     0 = failure, reading DAC instance was not successful (returns NULL)
 *     n = success, reading DAC instance was successful (returns 16-bit wide pointer)
 * 
 * Description:
 *     This function reads all registers with their current configuration into
 *     a data structure of type P33C_DAC_INSTANCE_s. Users can read and 
 *     verify or modify the configuration to write it back to the DAC instance  
 *     registers or copy configurations to other instances of the same type.
 * 
 * ********************************************************************************/

volatile struct P33C_DAC_INSTANCE_s p33c_DacInstance_ConfigRead(volatile uint16_t dacInstance)
{
    volatile struct P33C_DAC_INSTANCE_s* dac;

    // Set pointer to memory address of desired DAC instance
    dac = (volatile struct P33C_DAC_INSTANCE_s*) 
        ((volatile uint8_t*) &DAC1CONL + ((dacInstance - 1) * P33C_DAC_SFR_OFFSET));

    return(*dac);
    
}

/* @@p33c_DacInstance_ConfigWrite
 * ********************************************************************************
 * Summary:
 *     Writes a user-defined configuration to the DAC instance registers
 * 
 * Parameters:
 *     (none)
 * 
 * Returns:
 *     0 = failure, writing DAC instance was not successful
 *     1 = success, writing DAC instance was successful
 * 
 * Description:
 *     This function writes a user-defined DAC instance configuration of type 
 *     P33C_DAC_INSTANCE_s to the DAC instance registers. The 
 *     individual register configurations have to be set in user-code 
 *     before calling this function. To simplify the configuration process
 *     of standard functions, this driver provides templates, which can be 
 *     loaded and written directly.
 * 
 * ********************************************************************************/

volatile uint16_t p33c_DacInstance_ConfigWrite(
        volatile uint16_t dacInstance, 
        volatile struct P33C_DAC_INSTANCE_s dacConfig
)
{
    volatile uint16_t retval=1;
    volatile struct P33C_DAC_INSTANCE_s* dac;    

    // Set pointer to memory address of desired DAC instance
    dac = (volatile struct P33C_DAC_INSTANCE_s*) 
        ((volatile uint8_t*) &DAC1CONL + ((dacInstance - 1) * P33C_DAC_SFR_OFFSET));
    *dac = dacConfig;
    
    return(retval);
    
}

/* ============================================================================== */
/* ============================================================================== */
/* ============================================================================== */


/* @@dacModuleConfigClear
 * ********************************************************************************
 * Summary:
 *   Default RESET configuration of the DAC module channel SFRs
 * 
 * Data type:
 *   struct dacConfigClear:
 *      DAC Module Special Function Register (SFR) set
 *
 * Description:
 *   Default configuration of the DAC module SFRs with all its registers 
 *   being reset to their default state when the device comes out of RESET.
 *   Programmers can use this template to reset (dispose) a previously used
 *   DAC module when it's not used anymore or to secure a known startup
 *   condition before writing individual configurations to its SFRs.
 * 
 * *******************************************************************************/

volatile struct P33C_DAC_MODULE_s dacModuleConfigClear = {

    .DacModuleCtrl1L.value = 0x0000,
    .DacModuleCtrl2L.value = 0x0000,
    .DacModuleCtrl2H.value = 0x0000

    };

/* @@dacConfigClear
 * ********************************************************************************
 * Summary:
 *   Default RESET configuration of one DAC instance channel SFRs
 * 
 * Data type:
 *   struct dacConfigClear:
 *      DAC instance Special Function Register (SFR) set
 *
 * Description:
 *   Default configuration of the DAC instance SFRs with all its registers 
 *   being reset to their default state when the device comes out of RESET.
 *   Programmers can use this template to reset (dispose) a previously used
 *   DAC instance when it's not used anymore or to secure a known startup
 *   condition before writing individual configurations to its SFRs.
 * 
 * *******************************************************************************/

volatile struct P33C_DAC_INSTANCE_s dacConfigClear = {
    
    .DACxCONL.value = 0x0000,
    .DACxCONH.value = 0x0000,
    .DACxDATL.value = 0x0000,
    .DACxDATH.value = 0x0000,
    .SLPxCONL.value = 0x0000,
    .SLPxCONH.value = 0x0000,
    .SLPxDAT.value  = 0x0000
        
    };

// ________________________
// end of file
