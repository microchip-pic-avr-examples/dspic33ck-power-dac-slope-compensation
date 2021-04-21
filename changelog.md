# dspic33ck-power-dac-slope-compensation, release v1.1.0

### Release Highlights
Simplified DAC configuration of example.

### Features Added\Updated
Updated DAC configuration with simplified parameter adjustment header file

# dspic33ck-power-dac-slope-compensation, release v1.0.0

### Release Highlights
This is the initial release demonstrating the basic configuration of DAC and high-resolution PWM generator of the dsPIC33C family of devices applying a negative compensation ramp to the reference of an analog comparator in a fixed frequency peak current mode controlled (PCMC) system. This example demonstrates the peripheral configuration of the comparator-driven switching cell covering the configuration of PWM generator, analog comparator and Digital-to-Analog converter with ramp generator in a static setup (no active control loop included).


### Features Added\Updated
In this initial version the on-board LED of the dsPIC33CK Digital Power Plug-In Module is toggled with a interval period of 300 ms, when the controller is running at maximum speed of 100 MIPS.
After startup, a 100mV/uS slope compensation ramp is generated at DACOUT1 pin. By pressing the on-board push button *USER* on the Digital Power Development Board, the slope rate is toggled between the initial 100mV/uS degrees and 300mV/uS.

