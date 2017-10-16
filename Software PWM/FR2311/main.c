#include <msp430.h> 


/**
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= BIT0;// pin output
    P1OUT |= BIT0; //turn on LED
    P2DIR |= BIT0;// P1.6 pin output
    P2OUT |= BIT0;//turn on LED

    P1REN |= BIT1; //Enable resistor for pin 1.3.
    P1OUT |= BIT1;


    TB0CTL |= TBIE; //enable TB0 interrupt
    TB0CCTL0 |= CCIE; //enable CCR0 interrupt
    TB0CCTL0 &= ~TBIFG; //clear flag
    TB0CCTL1 |= CCIE; //enable CCR1 interrupt
    TB0CCTL1 &= ~TBIFG;//clear flag

    TB0CTL = TBSSEL_2 + MC_1 + ID_0; // SMCLK, upmode, clk/1
    TB0CCR1 = 500; //50% duty
    TB0CCR0 = 1000;  //1 kHz signal



    __bis_SR_register(GIE);  //not low power mode
    while(1){

        if ((P1IN & BIT1) != BIT1) { //Listen for button presses.
            P2OUT |= BIT0;
            __delay_cycles(200000);
            TB0CCR1 = TB0CCR1 + 100; //Increment the PWM period
        if (TB0CCR1 > 1000) { TB0CCR1 = 0; }
        else {P2OUT &= ~BIT0;}

        }



    }

}

#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void) { //a0 interrupt
    P1OUT |= BIT0; //turn on led 1.0
}

#pragma vector = TIMER0_B1_VECTOR
__interrupt void Timer0_B1_ISR(void) { //a1 interrupt
   switch(TB0IV){
   case 2://CCR1
   P1OUT &= ~BIT0; //turn off led 1.0
  //  break;
    }
}
