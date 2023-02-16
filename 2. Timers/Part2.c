/*
 * Part2.c
 *
 *  Created on: Feb 16, 2023
 *      Author: Caleb Amadoro
 *
 *      This code will need to change the speed of an LED between 3 different speeds by pressing a button.
 */

#include <msp430.h>

int delay = 20000;

void gpioInit();
void timerInit();

void main(){

    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

    gpioInit();
    timerInit();

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    __bis_SR_register(LPM3_bits | GIE);

}


void gpioInit(){
    // @TODO Initialize the Red or Green LED
    P6OUT &= ~BIT6;                         // Clear P6.6 output latch for a defined power-on state
    P6DIR |= BIT6;                          // Set P6.6 to output direction
    // @TODO Initialize Button 2.3
    P2OUT |= BIT3;                          // Configure P2.3 as pulled-up
    P2REN |= BIT3;                          // P2.3 pull-up register enable
    P2IES |= BIT3;                          // P2.3 High --> Low edge
    P2IE |= BIT3;                           // P2.3 interrupt enabled
}

void timerInit(){
    // @TODO Initialize Timer B1 in Continuous Mode using ACLK as the source CLK with Interrupts turned on
    TB1CTL = ID_0 | TBSSEL_1 | MC_2;
    TB1CCTL0 = CCIE;
    TB1CCR0 = 50000;
}


//INTERRUPT ROUTINES

// Port 2 interrupt service routine
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    // @TODO Remember that when you service the GPIO Interrupt, you need to set the interrupt flag to 0.
    P2IFG &= ~BIT3;
    // @TODO When the button is pressed, you can change what the CCR0 Register is for the Timer. You will need to track what speed you should be flashing at.
    if (delay == 20000){
        delay = 5000;
    }
    else if (delay == 5000){
        delay = 1000;
    }
    else if (delay == 1000){
        delay = 20000;
    }
}

// Timer B1 interrupt service routine
#pragma vector = TIMER1_B0_VECTOR
__interrupt void Timer1_B0_ISR(void)
{
    P6OUT ^= BIT6;
    TB1CCR0 += delay;
}



