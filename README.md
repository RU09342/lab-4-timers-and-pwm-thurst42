# Lab 4: Timers and PWM

#Gray Thurston 

# Button Debounce Using Timer.

##Introduction 

The purpose of this lab is to debounce a button in software using the msp430's 
Timer A module and then ultimatly toggle on of the on board leds. To do this 
we needed to use an interurrpt service routine triggered by one of the onboard buttons.
In the button interrupt serivce routine we need to toggle the led and the start timer A 
Only when the button has setteled is timer A allowed to count to the value in the 
assosiated capture and compare register. When this happens another interrupt is triggered 
which resets the interupt flag. Thus debounceing the switch.]

##Implimented Devices
* MSP430F5529
* MSP430FR2311
* MSP430FR5994
* MSP430FR6989
* MSP430G2553

##Functionality 

This code debounces the onboard switch and toggles the state of the LED. Debounce accomplished 
using timer A. 

##Errors

No known errors exist. 

# HARDWARE PWM

##Introduction 

The purpose of this lab is to start to start to use some of the advanced feature of the 
MSP430's timers. To complete this lab we need to recreate the same functionality as in 
the software PWM. To do that we used the PxSEL register to output the timer signal directly 
onto the pin. This giving us our PWM signal without all the hassel involved in the software
PWM lab.

##Implimented Devices
* MSP430F5529
* MSP430FR2311
* MSP430FR5994
* MSP430FR6989
* MSP430G2553

##Errors

No known errors exist.


