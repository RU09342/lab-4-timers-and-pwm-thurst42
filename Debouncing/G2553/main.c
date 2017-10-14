#include <msp430g2553.h>

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // disable watchdog timer
    P1DIR |= BIT6;            // set output
    P1DIR &= ~BIT3;            // Set input
    P1REN |= BIT3;            // resistor enable...
    P1OUT |= BIT3;            // pullup resistor
    P1IE |= BIT3;             //  interrupt pin

    TA0CCTL0 = CCIE;          // enable capture/compare interrupt
    __enable_interrupt();     // enable interrupt code
    while(1)
    {}              // run
}

#pragma vector=PORT1_VECTOR   // interrupt vector
__interrupt void button(void) // interrupt function
{

    P1IE &= !BIT3; // disbale interupt
    P1OUT ^= BIT6;     // toggle led
    TA0CTL = TASSEL_1 + MC_1 + TACLR; // Set Timer A0 to ACLK, up mode
    TA0CCR0 = 1000;  // count
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void timer(void)
{
    TA0CTL = MC_0;       // stop timer
    TA0R = 0;       // reset count
    P1IE |= BIT3;  // enable interrupt
    P1IFG = ~BIT3;  // disable interrupt flag
}
