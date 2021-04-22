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

/*@@p33c_dac.h
 * ************************************************************************************************
 * Summary:
 * Generic Digital-To-Analog Converter Driver Module (header file)
 *
 * Description:
 * This additional header file contains defines for all required bit-settings of all related 
 * special function registers of a peripheral module and/or instance. 
 * This file is an additional header file on top of the generic device header file.
 * 
 * See Also:
 *	p33c_dac.c
 * ***********************************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef P33C_DAC_SFR_ABSTRACTION_H
#define	P33C_DAC_SFR_ABSTRACTION_H

// Include standard header files
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types


// GENERIC PDM DAC MODULE SPECIAL FUNCTION REGISTER SET
#ifndef P33C_DAC_MODULE_s

    struct P33C_DAC_MODULE_s{
        union {
            struct tagDACCTRL1LBITS bits; // Register bit-field
            uint16_t value : 16; // 16-bit wide register value
        } DacModuleCtrl1L;    // (DACCTRL1L) DAC CONTROL 1 REGISTER LOW
        unsigned : 16;         // (reserved/empty memory gap)
        union {
            struct tagDACCTRL2LBITS bits; // Register bit-field
            uint16_t value : 16; // 16-bit wide register value
        } DacModuleCtrl2L;    // (DACCTRL2L) DAC CONTROL 2 REGISTER LOW
        union {
            struct tagDACCTRL2HBITS bits; // Register bit-field
            uint16_t value : 16; // 16-bit wide register value
        } DacModuleCtrl2H;    // (DACCTRL2H) DAC CONTROL 2 REGISTER HIGH
    }; 
    typedef struct P33C_DAC_MODULE_s P33C_DAC_MODULE_t; // PDM DAC MODULE REGISTER SET

#endif

// GENERIC PDM DAC INSTANCE SPECIAL FUNCTION REGISTER SET
#ifndef P33C_DAC_INSTANCE_s    
    
    struct P33C_DAC_INSTANCE_s {
        union {
            struct tagDAC1CONLBITS bits; // Register bit-field
            uint16_t value : 16; // 16-bit wide register value
        } DACxCONL; // DACxCONL: DACx CONTROL LOW REGISTER
        union {
            struct tagDAC1CONHBITS bits; // Register bit-field
            uint16_t value : 16; // 16-bit wide register value
        } DACxCONH; // DACxCONH: DACx CONTROL HIGH REGISTER
        union {
            struct tagDAC1DATLBITS bits; // Register bit-field
            uint16_t value : 16; // 16-bit wide register value
        } DACxDATL; // DACxDATL: DACx DATA LOW REGISTER
        union {
            struct tagDAC1DATHBITS bits; // Register bit-field
            uint16_t value : 16; // 16-bit wide register value
        } DACxDATH; // DACxDATH: DACx DATA HIGH REGISTER
        union {
            struct tagSLP1CONLBITS bits; // Register bit-field
            uint16_t value : 16; // 16-bit wide register value
        } SLPxCONL; // SLPxCONL: DACx SLOPE CONTROL LOW REGISTER
        union {
            struct tagSLP1CONHBITS bits; // Register bit-field
            uint16_t value : 16; // 16-bit wide register value
        } SLPxCONH; // SLPxCONH: DACx SLOPE CONTROL HIGH REGISTER
        union {
            struct tagSLP1DATBITS bits; // Register bit-field
            uint16_t value : 16; // 16-bit wide register value
        } SLPxDAT;  // SLPxDAT: DACx SLOPE DATA REGISTER
    }; // PDM DAC INSTANCE REGISTER SET
    typedef struct P33C_DAC_INSTANCE_s P33C_DAC_INSTANCE_t; // PDM DAC INSTANCE REGISTER SET
    
    #define P33C_DAC_SFR_OFFSET  ((uint16_t)&DAC2CONL - (uint16_t)&DAC1CONL)

#endif

// Declare macro for getting start memory address of DAC module data structure
#define p33c_DacModule_GetHandle()      (P33C_DAC_MODULE_t*)&DACCTRL1L

// Declare macro for getting start memory address of DAC instance data structure
#if defined (DAC4CONL)
#define p33c_DacInstance_GetHandle(x)   (P33C_DAC_INSTANCE_t*)&DAC1CONL, (P33C_DAC_INSTANCE_t*)&DAC2CONL, \
                                        (P33C_DAC_INSTANCE_t*)&DAC3CONL, (P33C_DAC_INSTANCE_t*)&DAC4CONL
#elif defined (DAC3CONL)
#define p33c_DacInstance_GetHandle(x)   (P33C_DAC_INSTANCE_t*)&DAC1CONL, (P33C_DAC_INSTANCE_t*)&DAC2CONL, \
                                        (P33C_DAC_INSTANCE_t*)&DAC3CONL
#elif defined (DAC2CONL)
#define p33c_DacInstance_GetHandle(x)   (P33C_DAC_INSTANCE_t*)&DAC1CONL, (P33C_DAC_INSTANCE_t*)&DAC2CONL
#elif defined (DAC1CONL)
#define p33c_DacInstance_GetHandle(x)   (P33C_DAC_INSTANCE_t*)&DAC1CONL 
#else
#pragma message "warning: no DAC instance support for the selected device"
#endif
    
/* ********************************************************************************************* * 
 * API FUNCTION PROTOTYPES
 * ********************************************************************************************* */

extern volatile uint16_t p33c_DacModule_Dispose(void);

extern volatile struct P33C_DAC_MODULE_s p33c_DacModule_ConfigRead(void);
extern volatile uint16_t p33c_DacModule_ConfigWrite(
                    volatile struct P33C_DAC_MODULE_s dacConfig
                );


extern volatile uint16_t p33c_DacInstance_Dispose(
                    volatile uint16_t dacInstance
                );

extern volatile struct P33C_DAC_INSTANCE_s p33c_DacInstance_ConfigRead(
                    volatile uint16_t dacInstance
                );

extern volatile uint16_t p33c_DacInstance_ConfigWrite(
                    volatile uint16_t dacInstance, 
                    volatile struct P33C_DAC_INSTANCE_s dacConfig
                );

/* ********************************************************************************************* * 
 * DAC INSTANCE CONFIGURATION TEMPLATES
 * ********************************************************************************************* */
extern volatile struct P33C_DAC_MODULE_s dacModuleConfigClear;
extern volatile struct P33C_DAC_INSTANCE_s dacConfigClear;


#endif	/* P33C_DAC_SFR_ABSTRACTION_H */
// END OF FILE
