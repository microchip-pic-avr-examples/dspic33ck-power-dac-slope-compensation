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
 * File:   pwm.h
 * Author: A14426
 * Comments: Header file of the user-configuration source file pwm.c
 * Revision history: 0
 * 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_PWM_INITIALIZATION_H
#define	XC_PWM_INITIALIZATION_H

#include <xc.h> // include processor files - each processor file is guarded.  

#include "common/p33c_pwm.h" // Include dsPIC33C standard PWM driver header file


 /* *********************************************************************************
 * USER DEFINED GLOBAL VARIABLE DECLARATIONS
 * ********************************************************************************/    
    
/* Declare global, user-defined PWM generator object */    
extern volatile struct P33C_PWM_GENERATOR_s* my_pg1; // pointer to user-defined leading PWM generator object 
extern volatile struct P33C_PWM_GENERATOR_s* my_pg3; // pointer to user-defined synchronized PWM generator object 

// Pre-compiler plausibility check if declared PWM generator index 
// points to an existing/available PWM generator on the selected device

#if (MY_PWM_GENERATOR > P33C_PG_COUNT)
  #pragma message "specified PWM generator peripheral instance not available (out of range)"
#endif

/* *********************************************************************************
 * USER FUNCTION PROTOTYPES
 * ********************************************************************************/    
    
extern volatile uint16_t PWM_Initialize(void);
extern volatile uint16_t PWM_Enable(void);
extern volatile uint16_t PWM_Disable(void);

extern volatile struct P33C_PWM_GENERATOR_s* my_pg1;    // user-defined PWM generator 1 object 


#endif	/* XC_PWM_INITIALIZATION_H */

