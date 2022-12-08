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
 * File:   demo.h
 * Author: M91406
 * Comments: 
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef DEMO_CODE_SETUP_H
#define	DEMO_CODE_SETUP_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types
#include <math.h>  // include standard math library

// Clock settings
#define CPU_CLOCK               (float) 100e+6  // CPU clock frequency in [Hz]
#define PWM_CLOCK               (float) 4.0e+9  // PWM timebase clock in [Hz]
#define AUX_CLOCK               (float) 500e+6  // Auxiliary Clock Frequency in [Hz]

// Default DAC peripheral declarations
#define DAC_REFERENCE           (float) 3.300   // DAC reference voltage (usually AVDD)
#define DAC_RESOLUTION          (float)12.000   // DAC resolution in [bit]
#define DAC_TRANSITION_TIME     (float)340e-9   // Transition Mode Time setting DA09 specified in data sheet
#define DAC_STEADY_STATE_TIME   (float)550e-9   // Steady-State Time setting DA10 specified in data sheet
#define DAC_LEADING_EDGE_BLNK   (float)120e-9   // DAC LEading Edge Blanking period
#define DAC_VOLTAGE_MAX         (float) 3.135   // Maximum DAC output voltage specification in data sheet, DA09
#define DAC_VOLTAGE_MIN         (float) 0.625   // Minimum DAC output voltage specification in data sheet, DA10


// PWM declarations
#define PWM_GENERATOR           1U // Specify index of leading PWM generator instance (1=PG1, 2=PG2, etc)
#define PWM_FREQUENCY           (float) 200e+3  // Default PWM frequency
#define PWM_DUTY_RATIO          (float) 0.25    // Default duty ratio setting
#define PWM_DEADTIME_RISING     (float) 50e-9   // Default rising edge dead time setting
#define PWM_DEADTIME_FALLING    (float) 80e-9   // Default falling edge dead time setting

// PWM Conversion Macros
#define PWM_RESOLUTION          (float)(1.0 / PWM_CLOCK) // Up to 250 ps PWM resolution 
#define PWM_PERIOD              (uint16_t)(float)((1.0 / PWM_FREQUENCY) / PWM_RESOLUTION) // Default PWM period
#define PWM_DUTY_CYCLE          (uint16_t)(PWM_PERIOD * PWM_DUTY_RATIO) // Default duty cycle value
#define PWM_DEAD_TIME_RE        (uint16_t)(PWM_DEADTIME_RISING  / PWM_RESOLUTION) // Default duty cycle value
#define PWM_DEAD_TIME_FE        (uint16_t)(PWM_DEADTIME_FALLING / PWM_RESOLUTION) // Default duty cycle value

// DAC declarations 
#define DAC_INSTANCE            1U // Specify index of DAC instance (1=DAC1, 2=DAC2, etc)
#define DAC_VOLTAGE_HIGH_1      (float) 1.800 // Demo-mode DAC level #1
#define DAC_VOLTAGE_HIGH_2      (float) 2.500 // Demo-mode DAC level #2
#define SLOPE_START_DELAY       (float) 0.10  // Delay in {%] until the slope compensation ramp starts
#define SLOPE_STOP_DELAY        (float) 0.90  // Delay in [%] until the slope compensation ramp stops
#define SLOPE_SLEW_RATE_1       (float) 0.200 // Delay in [V/µs] 
#define SLOPE_SLEW_RATE_2       (float) 0.400 // Delay in [V/µs] 

// DAC Conversion Macros
#define DAC_GRANULARITY         (float)(DAC_REFERENCE / pow(2.0, DAC_RESOLUTION)) // DAC granularity in [V/tick]
#define DAC_CLOCK_FREQUENCY     (float) AUX_CLOCK   // DAC input clock in [Hz]
#define DAC_CLOCK_PERIOD        (float)(2.0 / DAC_CLOCK_FREQUENCY) // DAC input clock (period) selected in [sec]
#define DAC_TMODTIME            (uint16_t)((DAC_TRANSITION_TIME * DAC_CLOCK_FREQUENCY) / 2.0)   // DAC Reset Transition Mode Period
#define DAC_SSTIME              (uint16_t)((DAC_STEADY_STATE_TIME * DAC_CLOCK_FREQUENCY) / 2.0) // Settling time period
#define DAC_TMCB                (uint16_t)((DAC_LEADING_EDGE_BLNK * DAC_CLOCK_FREQUENCY) / 2.0) // DACx Leading-Edge Blanking

#define SLP_TRIG_START          (uint16_t)(PWM_PERIOD * SLOPE_START_DELAY) // Delay in {sec] until the slope compensation ramp starts
#define SLP_TRIG_STOP           (uint16_t)(PWM_PERIOD * SLOPE_STOP_DELAY) // Delay in {sec] until the slope compensation ramp stops
#define SLP_SLEW_RATE_1         (uint16_t)((16.0 * (SLOPE_SLEW_RATE_1 / DAC_GRANULARITY)) / (1.0e-6 / DAC_CLOCK_PERIOD)) // SLOPE DATA in [<DAC ticks>/<CLK-ticks>] representing [V/usec]
#define SLP_SLEW_RATE_2         (uint16_t)((16.0 * (SLOPE_SLEW_RATE_2 / DAC_GRANULARITY)) / (1.0e-6 / DAC_CLOCK_PERIOD)) // SLOPE DATA in [<DAC ticks>/<CLK-ticks>] representing [V/usec]
#define SLP_PERIOD              (float)((SLOPE_STOP_DELAY-SLOPE_START_DELAY)*PWM_PERIOD) // Slope duration from START to STOP

#define DACOUT_VALUE_HIGH_1     (uint16_t)(DAC_VOLTAGE_HIGH_1 / DAC_GRANULARITY)
#define DACOUT_VALUE_HIGH_2     (uint16_t)(DAC_VOLTAGE_HIGH_2 / DAC_GRANULARITY)


#endif	/* DEMO_CODE_SETUP_H */

