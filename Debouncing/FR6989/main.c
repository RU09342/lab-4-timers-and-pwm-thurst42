#include <msp430.h>

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // disable watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= BIT0;            // set output
    P1DIR &= ~BIT1;            // Set input
    P1REN |= BIT1;            // resistor enable...
    P1OUT |= BIT1;            // pullup resistor
    P1IE |= BIT1;             //  interrupt pin

    TA0CCTL0 = CCIE;          // enable capture/compare interrupt
    __enable_interrupt();     // enable interrupt code
    while(1)
    {}              // run
}

#pragma vector=PORT1_VECTOR   // interrupt vector
__interrupt void button(void) // interrupt function
{

    P1IE &= !BIT1; // disbale interupt
    P1OUT ^= BIT0;     // toggle led
    TA0CTL = TASSEL_1 + MC_1 + TACLR; // Set Timer A0 to ACLK, up mode
    TA0CCR0 = 1000;  // count
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void timer(void)
{
    TA0CTL = MC_0;       // stop timer
    TA0R = 0;       // reset count
    P1IE |= BIT1;  // enable interrupt
    P1IFG = ~BIT1;  // disable interrupt flag
}

