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
 * File: dac.h 
 * Author: A14426
 * Comments: Header file of the user-configuration source file dac.c
 * Revision history: Initial Release
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_DAC_INITIALIZATION_H
#define	XC_DAC_INITIALIZATION_H

#include <xc.h> // include processor files - each processor file is guarded.  

#include "common/p33c_dac.h"
 

#define AUX_FREQUENCY       500e+6   // Auxiliary Clock Frequency in [Hz]

//PWM Settings

#define PWM_OUT_FREQUENCY    200e+3
#define PWM_OUT_PERIOD       (1.0/PWM_OUT_FREQUENCY)
#define PWM_RESOLUTION       250e-12  // Up to 250 ps PWM Resolution given in Data Sheet
#define PWM_PERIOD           (volatile uint16_t)(PWM_OUT_PERIOD/PWM_RESOLUTION) 

#define PWM_DUTY_RATIO      (double) 0.20
#define PWM_DUTY_CYCLE      (volatile uint16_t) (PWM_PERIOD* PWM_DUTY_RATIO)

// DAC settings 
#define DAC1                      1
#define DAC_VOLTAGE_HIGH       (double) 3.0
#define DAC_VOLTAGE_LOW_1      (double) 2.625
#define DAC_VOLTAGE_LOW_2      (double) 1.875 

#define SLOPE_START_DELAY      (double) 0.20  // Delay in {%] until the slope compensation ramp starts
#define SLOPE_STOP_DELAY       (double) 0.95 // Delay in [%] until the slope compensation ramp stops

#define SLP_TRIG_START   (uint16_t)(PWM_PERIOD * SLOPE_START_DELAY) // Delay in {sec] until the slope compensation ramp starts
#define SLP_TRIG_STOP    (uint16_t)(PWM_PERIOD * SLOPE_STOP_DELAY) // Delay in {sec] until the slope compensation ramp stops


#define DAC_REF         (double)3.300           // DAC reference voltage (usually AVDD)
#define DAC_RES         (double)12.00           // DAC resolution in [bit]
#define DAC_GRAN        (double)(DAC_REF /4096)  // DAC granularity in [V/tick]
#define FDAC            (double)AUX_FREQUENCY   // DAC input clock in Hz
#define DACCLK          (double)(2.0/FDAC)      // DAC input clock (period) selected in [sec]

 
#define DAC_T_RESET     300e-9  // Transition Mode Duration
#define DAC_T_SETTLING  350e-9  // Time from Start of Transition Mode until Steady-State Filter is Enabled



#define DAC_TMODTIME    (uint16_t)((DAC_T_RESET * FDAC)/2.0)            // Transition Mode Duration
#define DAC_SSTIME      (uint16_t)((DAC_T_SETTLING * FDAC)/2.0)         // Time from Start of Transition Mode until Steady-State Filter is Enabled

#define TSLOPE_DURATION    (double)((SLOPE_STOP_DELAY-SLOPE_START_DELAY)*PWM_OUT_PERIOD ) // Slope duration from START to STOP

#define DACOUT_VALUE_LOW_1      (uint16_t)(DAC_VOLTAGE_LOW_1 / DAC_GRAN)
#define DACOUT_VALUE_LOW_2      (uint16_t)(DAC_VOLTAGE_LOW_2 / DAC_GRAN)
#define DACOUT_VALUE_HIGH       (uint16_t)(DAC_VOLTAGE_HIGH / DAC_GRAN)

#define DELTA_DACOUT_1    (double)(DAC_VOLTAGE_HIGH-DAC_VOLTAGE_LOW_1) // change in DAC voltage 1
#define DELTA_DACOUT_2    (double)(DAC_VOLTAGE_HIGH-DAC_VOLTAGE_LOW_2) // change in DAC voltage 2

#define DAC_SLOPE_RATE_1  (uint16_t)((16.0 * (DELTA_DACOUT_1 / DAC_GRAN)) / ((TSLOPE_DURATION/DACCLK) + 1.0)) // SLOPE DATA in [DAC-ticks/CLK-tick]
#define DAC_SLOPE_RATE_2  (uint16_t)((16.0 * (DELTA_DACOUT_2 / DAC_GRAN)) / ((TSLOPE_DURATION/DACCLK) + 1.0)) // SLOPE DATA in [DAC-ticks/CLK-tick]



extern volatile uint16_t  DAC_Initialize(void);

extern volatile struct P33C_DAC_MODULE_s* my_dac_module;
extern volatile struct P33C_DAC_INSTANCE_s* my_dac_instance;


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

