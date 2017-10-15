#include <msp430.h>

int main(void) {
WDTCTL = WDTPW + WDTHOLD;
PM5CTL0 &= ~LOCKLPM5;
    P2DIR |= BIT0; //Set pin 1.2 to the output direction
    P1DIR |= BIT0;



    P1REN |= BIT1; //Enable resistor for pin 1.3.
    P1OUT |= BIT1;
    P2SEL0 |= BIT0;
    TB1CCR0 = 1000; //The timer counts up to this.
    TB1CCTL1 = OUTMOD_7;
    TB1CCR1 = 500; //The PWM period, which is 0 uS.
    TB1CTL = TBSSEL_2 + MC_1;

while(1)
{
    if ((P1IN & BIT1) != BIT1) { //Listen for button presses.
        P1OUT |= BIT0;
        __delay_cycles(100000);
        TB1CCR1 = TB1CCR1 + 100; //Increment the PWM period
    if (TB1CCR1 > 1000) { TB1CCR1 = 0; }
    else {P1OUT &= ~BIT0;}

    }
}

}
