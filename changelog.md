# dspic33ck-power-dac-slope-compensation, release v1.0.0

### Release Highlights
This is the initial release demonstrating the basic configuration of DAC and  high-resolution PWM generator of the dsPIC33C family of devices.
This example is part of a series of code examples highlighting specific operating modes and features.

### Features Added\Updated
In this intial version the on-board LED of the dsPIC33CK Digital Power Plug-In Module is toggled with a interval üperiod of 300 ms, when the controller is running at maximum speed of 100 MIPS.
After startup, a 100mV/uS slope compensation ramp is generated at DACOUT1 pin. By pressing the on-board push button *USER* on the Digital Power Develpoment Board, the slope rate is toggled between the initial 100mV/uS degrees and 300mV/uS.
