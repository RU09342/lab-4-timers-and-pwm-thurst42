#include <msp430.h>

int main(void) {
WDTCTL = WDTPW + WDTHOLD;
PM5CTL0 &= ~LOCKLPM5;
    P1DIR |= BIT1; //Set pin 1.2 to the output direction
    P1DIR |= BIT0;



    P5REN |= BIT6; //Enable resistor for pin 1.3.
    P5OUT |= BIT6;
    P1SEL0 |= BIT0;
    TA1CCR0 = 1000; //The timer counts up to this.
    TA1CCTL1 = OUTMOD_7;
    TA1CCR1 = 500; //The PWM period, which is 0 uS.
    TA1CTL = TASSEL_2 + MC_1;

while(1)
{
    if ((P5IN & BIT6) != BIT6) { //Listen for button presses.
        P1OUT |= BIT1;
        __delay_cycles(100000);
        TA1CCR0 = TA1CCR0 + 100; //Increment the PWM period
    if (TA1CCR0 > 1000) { TA1CCR0 = 0; }
    else {P1OUT &= ~BIT1;}

    }
}

}
