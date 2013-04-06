// See http://homepages.ius.edu/rwisman/C335/html/Syllabus.htm
//
// A push of the button P1.3 increases the stored value by 1. Output is binary.
// Note: The button bounces

#include <msp430.h>
#include <legacymsp430.h>

#define SLEEP (15000U)

#define LED1 (1<<0)
#define LED2 (1<<6)

#define BTN  (1<<3)

volatile unsigned int count;

int main(void) {
	#define CBITS (6)
	volatile unsigned int i;
	int n;

	WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

	P1DIR |=  LED1; // Set P1.0 (red LED) to output
	P1OUT &= ~LED1; // Turn LED off

	P1DIR |=  LED2; // Set P1.6 (green LED) to output
	P1OUT &= ~LED2; // Turn LED off

	P1SEL &= ~BTN;	// Select Button
	P1DIR &= ~BTN;	// Select as Input (in = 0, out = 1)
	P1REN |=  BTN;	// Pull-Up Resistor

	P1IE  |=  BTN;	// Generate interrupt
	P1IFG &= ~BTN;	// Clear Interrupt

	_BIS_SR(GIE);	// Enable Interrupts
	
	count = 0;
	while (1) {
		// sync: 2 SLEEP green, red off
		P1OUT |=  LED2;
		//P1OUT &= ~LED1;
		for (i=0; i<2*SLEEP; i++);

		// output C binary
		for (n = (CBITS-1); n >= 0; n--) {
			// toggle red LED
			if (count & (1<<n)) {
				P1OUT |=  LED1;
			} else {
				P1OUT &= ~LED1;
			}
			// toggle green LED (clock)
			P1OUT &= ~LED2;
			for (i=0; i<SLEEP; i++);
			P1OUT |=  LED2;
			for (i=0; i<SLEEP; i++);
		}
	}
	return 0;
}

#pragma vector=PORT1_VECTOR
__interrupt void incrementor(void) {
	P1IFG &= ~BTN;	// Clear Interrupt
	count = count + 1;
}
