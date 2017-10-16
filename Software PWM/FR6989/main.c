#include <msp430.h> 


/**
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= BIT0;// pin output
    P1OUT |= BIT0; //turn on LED
    P9DIR |= BIT7;// P1.6 pin output
    P9OUT |= BIT7;//turn on LED

    P1REN |= BIT1; //Enable resistor for pin 1.3.
    P1OUT |= BIT1;


    TA0CTL |= TAIE; //enable TA0 interrupt
    TA0CCTL0 |= CCIE; //enable CCR0 interrupt
    TA0CCTL0 &= ~TAIFG; //clear flag
    TA0CCTL1 |= CCIE; //enable CCR1 interrupt
    TA0CCTL1 &= ~TAIFG;//clear flag

    TA0CTL = TASSEL_2 + MC_1 + ID_0; // SMCLK, upmode, clk/1
    TA0CCR1 = 500; //50% duty
    TA0CCR0 = 1000;  //1 kHz signal



    __bis_SR_register(GIE);  //not low power mode
    while(1){

        if ((P1IN & BIT1) != BIT1) { //Listen for button presses.
            P9OUT |= BIT7;
            __delay_cycles(200000);
            TA0CCR1 = TA0CCR1 + 100; //Increment the PWM period
        if (TA0CCR1 > 1000) { TA0CCR1 = 0; }
        else {P9OUT &= ~BIT7;}

        }



    }

}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR(void) { //a0 interrupt
    P1OUT |= BIT0; //turn on led 1.0
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void Timer0_A1_ISR(void) { //a1 interrupt
   switch(TA0IV){
   case 2://CCR1
   P1OUT &= ~BIT0; //turn off led 1.0
  //  break;
    }
}
