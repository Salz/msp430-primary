// toggle LED1 while being in low power mode

#include <msp430.h>
#include <legacymsp430.h>

#define LED1 (1<<0)
#define LED2 (1<<6)

#define BTN (1<<3)

int main(void) {
	WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

	P1DIR |=  LED1; // Set P1.0 (red LED) to output
	P1OUT &= ~LED1; // Turn LED off

	P1SEL &= ~BTN;	// Select Button
	P1DIR &= ~BTN;	// Select as Input (in = 0, out = 1)
	P1REN |=  BTN;	// Pull-Up Resistor

	P1IE  |=  BTN;	// Generate interrupt
	P1IFG &= ~BTN;	// Clear Interrupt

	_BIS_SR(LPM4_bits + GIE); // Enable low power (1uA) and interrupts

	for(;;);
}

#pragma vector=PORT1_VECTOR
__interrupt void toggle(void) {
	P1IFG &= ~BTN;	// Clear Interrupt
	P1OUT ^= LED1;	// Toggle LED
}
