#include <msp430.h>

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // disable watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= BIT0;            // set output
    P5DIR &= ~BIT5;            // Set input
    P5REN |= BIT5;            // resistor enable...
    P5OUT |= BIT5;            // pullup resistor
    P5IE |= BIT5;             //  interrupt pin

    TA0CCTL0 = CCIE;          // enable capture/compare interrupt
    __enable_interrupt();     // enable interrupt code
    while(1)
    {}              // run
}

#pragma vector=PORT5_VECTOR   // interrupt vector
__interrupt void button(void) // interrupt function
{

    P5IE &= !BIT5; // disbale interupt
    P1OUT ^= BIT0;     // toggle led
    TA0CTL = TASSEL_1 + MC_1 + TACLR; // Set Timer A0 to ACLK, up mode
    TA0CCR0 = 1000;  // count
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void timer(void)
{
    TA0CTL = MC_0;       // stop timer
    TA0R = 0;       // reset count
    P5IE |= BIT5;  // enable interrupt
    P5IFG = ~BIT5;  // disable interrupt flag
}
