/*
 * Part3.c
 *
 *  Created on: Mar 2, 2023
 *  Author: Caleb Amadoro
 */

#include <msp430.h>

int count = 2048;                           // initially set count to a 1 second duty cycle

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // turn on gpio

    P1OUT &= ~BIT0;                         // configure red LED as output
    P1DIR |= BIT0;

    P2OUT |= BIT3;                          // initialize P2.3 as input with pull-up resistor, measures high to low edge
    P2REN |= BIT3;
    P2IES |= BIT3;
    P2IE |= BIT3;

    P4OUT |= BIT1;                          // initialize P4.1 as input with pull-up resistor, measures high to low edge
    P4REN |= BIT1;
    P4IES |= BIT1;
    P4IE |= BIT1;

    TB1CTL = ID_3 | TBSSEL_1 | MC_2;        // timer B0 turns on default speed
    TB1CCTL0 |= CCIE;
    TB1CCR0 = count;

    __bis_SR_register(LPM3_bits | GIE);
}

#pragma vector=PORT4_VECTOR                 // when button 4.1 is triggered
__interrupt void Port_4(void)
{
    P4IFG &= ~BIT1;                         // reset interrupt flag
    count = 2048;                           // set count to default
}

#pragma vector=PORT2_VECTOR                 // when button 2.3 is triggered
__interrupt void Port_2(void)
{
    P2IFG &= ~BIT3;                         // reset interrupt flag

    if (!(P2IN & BIT3)){                    // when 2.3 is pressed in
        P2IES &= ~BIT3;                     // look for low to high edge
        TB1R = 0;                           // reset timer value
        P1OUT &= ~BIT0;                     // turn red led off

    } else {                                // when 2.3 is let go
        P2IES |= BIT3;                      // go back to looking for high to low edge
        count = TB1R;                       // count equals timer value
        TB1R = 0;                           // reset timer value
        TB1CCR0 = count;                    // set CCR0 to count value
        P1OUT |= BIT0;                      // turn LED on
    }
}

#pragma vector = TIMER1_B0_VECTOR           // when timer goes off
__interrupt void Timer1_B0_ISR(void)
{
    P1OUT^=BIT0;                            // toggle led
    TB1CCR0 += count;
}
