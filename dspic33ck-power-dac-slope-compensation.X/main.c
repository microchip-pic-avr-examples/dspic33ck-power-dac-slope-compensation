/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.1
        Device            :  dsPIC33CK256MP506
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.70
        MPLAB 	          :  MPLAB X v5.50
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include <xc.h>
#include "mcc_generated_files/system.h"
#include "main.h"

/* ********************************************************************* *
 * DAC Slope Compensation Ramp  Configuration Example
 * 
 * Description:
 * 
 *   This code example shows the basic configuration of DAC Slope Compensation ramp   
 *   using PWM Generator 1 (PG1) as trigger time base. The initial ramp slope rate   
 *   is set to 100mV/uS after start up and the ramp is available at the DAC 1 output (TP3). 
 *   By pressing push button [USER],the ramp slope rate is stepped to 300mV/uS. By pressing [USER] again,   
 *   the slope rate switches back to 100mV/uS.PG1 PWM1H output pin is used to trigger the start and end  
 *   of the ramp slope. The frequency and duty ratio of PG1 will always remain at 200Khz and 
 *   20% respectively.
 * 
 * Please note:
 *   This code example can be run on dsPIC33CK as well as on dsPIC33CH
 *   devices. The PWM outputs of each device may be routed to different
 *   test points. Please refer to the table below to quickly find the 
 *   right signal outputs. 
 * 
 * Recommended Use of this example:
 *   In this example Microchip Code Configurator (MCC) is used to set 
 *   up the device main and auxiliary clock as well as Timer1 used
 *   to create a deterministic execution of code within the main() 
 *   loop.The project folder 'common' contains generic PWM module 
 *   driver files,which are independent from MCC to better demonstrate 
 *   the PWM generator register configuration in more detail. 
 *   These driver files are providing an abstraction layer of the 
 *   user code, allowing quick migration of code across different 
 *   device peripherals and device families.
 * 
 *   To better understand these mechanisms please open file 'pwm.h' on
 *   code line 49 and change the following PWM generator index number to
 *   configure another PWM generator than #1.
 *
 *     #define PWM_GENERATOR     1 
 *     
 * 
 *   Valid numbers are 1-8 for PG1 through PG8 on dsPIC33CK and 
 *   1-4 for PG1 through PG4 on dsPIC33CH. Due to hardware limitations
 *   not all PWM generator outputs may be accessible. Please refer to 
 *   the Test Pin table below to review if the selected PWM generator 
 *   outputs are available and accessible.
 * 
 * Hardware:
 *  - Digital Power Development Board (DM330029) 
 *  - dsPIC33CK Digital Power Plug-In Module (MA330048)
 *
 * Software:
 *  - MPLAB X IDE, v5.40
 *  - Microchip Code Configuration (MCC), v4.0.1
 *  - XC16 C-Compiler, v1.50
 *  - dsPIC33CK-MP Device File Pack v1.4.102
 * 
 * ********************************************************************* */  

/* ********************************************************************* *
 * Digital Power Development Board (DM330029) Test Pin Assignment:
 * *********************************************************************
 * 
 * Board Overview:
 * 
 *         ------------------------------------
 *        |        DIGITAL TEST POINTS         |
 *        |------------------------------------|
 *        |           __________           ----|
 *        |          |__________|         | USB|
 *        |         DP PIM SOCKET          ----|
 *        |                               -----|
 *        |                   RESET O    | ICSP|
 *        |      _   _                    -----|
 *        |   P2|O| |O|P1      USER O          |
 *         ------------------------------------ 
 * 
 * Signal     | Test-Pin              | Comment
 *            | dsPIC33CK | dsPIC33CH | 
 * ---------------------------------------------------------------------
 * PWM1H      | TP45      | TP35      | PWM Generator #1 output HIGH
 * PWM1L      | TP47      | TP38      | PWM Generator #1 output LOW
 *            |           |           | 
 * PWM2H      | TP42      | TP25      | PWM Generator #2 output HIGH
 * PWM2L      | TP40      | TP27  (2) | PWM Generator #2 output LOW
 *            |           |           | 
 * PWM3H      | TP37      | TP36      | PWM Generator #3 output HIGH
 * PWM3L      | TP41      | TP34      | PWM Generator #3 output LOW
 *            |           |           | 
 * PWM4H      | TP43      | TP46      | PWM Generator #4 output HIGH
 * PWM4L      | TP44      | TP48      | PWM Generator #4 output LOW
 *            |           |           | 
 * PWM5H      | TP35      | (n/a) (3) | PWM Generator #5 output HIGH
 * PWM5L      | TP38      | (n/a) (3) | PWM Generator #5 output LOW
 *            |           |           | 
 * PWM6H      | TP31      | (n/a) (3) | PWM Generator #6 output HIGH
 * PWM6L      | TP33      | (n/a) (3) | PWM Generator #6 output LOW
 *            |           |           | 
 * PWM7H      | TP25      | (n/a) (3) | PWM Generator #7 output HIGH
 * PWM7L      | TP27 (1)  | (n/a) (3) | PWM Generator #7 output LOW
 *            |           |           | 
 * PWM8H      | TP46      | (n/a) (3) | PWM Generator #8 output HIGH
 * PWM8L      | TP48      | (n/a) (3) | PWM Generator #8 output LOW
 * ---------------------------------------------------------------------
 *
 * (1): not available on dsPIC33CK DP PIM; Shared with on-board push button SW1
 * (2): not available on dsPIC33CH DP PIM Master Core; Shared with on-board push button SW1
 * (3): not available on dsPIC33CH DP PIM Master Core
 * 
 * ********************************************************************* */

// Digital Power Plug-In Module On-Board LED control
#define LED_INTERVAL    5000
volatile uint16_t dbgled_cnt = 0;


/*
                         Main application
 */
int main(void)
{
    volatile uint16_t retval=1; // Local function return verification variable
    volatile uint16_t test_level=1;
    
    // initialize the device
    SYSTEM_Initialize();
    
    // User PWM Initialization
    retval &= PWM_Initialize();
    
    // User DAC Initialization
    retval &= DAC_Initialize();
    
    // Initialize DP PIM and DP DevBoard function pins
    _T1IF = 0;
    DBGPIN_InitAsOutput();
    DBGLED_InitAsOutput();
    SW_InitAsInput();
    TP03_InitAsOutput();
    
    // Enable PWM and DAC peripherals
    retval &= PWM_Enable(); // Turn on PWM module and user-specified instance
    retval &= DAC_Enable(); // Turn on DAC module and user-specified instance
    
    /* main loop */
    while (1)
    {
        while(!_T1IF);  // Wait for Timer1 to expire
        _T1IF = 0;      // Reset interrupt flag bit
        DBGPIN_Clear(); // Clear device debug pin
        
        // Count main-loop execution cycles until on-board LED needs to be toggled
        if(++dbgled_cnt > LED_INTERVAL)
        {
            dbgled_cnt = 0;     // Reset LED toggle counter
            DBGLED_Toggle();    // Toggle on-board LED
        }
        
        // Check if on-board push button has been pressed
        if (SW_Read() == SW_PRESSED)
        {
            // Wait until switch is released
            while(SW_Read() == SW_PRESSED); 

            // Update PWM timing registers
            switch (test_level)   // If DAC is set to test level #1, switch to #2
            {
                case 1:
                    my_dac->DACxDATH.value = DACOUT_VALUE_HIGH_2; // Decrease the DAC Lower value to increase the Slope rate
                    my_dac->SLPxDAT.value = SLP_SLEW_RATE_2; // DAC slope rate is set to 400mV/uS
                    test_level = 2;
                    break;

                default:    // Set DAC to test level #1
                    my_dac->SLPxDAT.value = SLP_SLEW_RATE_1; // DAC slope rate is set to 200mV/uS
                    my_dac->DACxDATH.value = DACOUT_VALUE_HIGH_1; // Decrease the DAC Lower value to increase the Slope rate
                    test_level = 1;
                    break;
            }

            // 
//            if(my_dac->SLPxDAT.bits.SLPDAT != SLP1DAT)
//            {
//                Nop();
//                Nop();
//                Nop();
//                Nop();
//            }
            
            DBGPIN_Set();  // Set debug pin as oscilloscope trigger
            
        }
        
    }
    
    return(1);  // If this line is ever reached, something really bad happened....
}
/**
 End of File
*/

