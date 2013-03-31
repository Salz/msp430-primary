// See http://homepages.ius.edu/rwisman/C335/html/Syllabus.htm

#include <msp430.h>
#include <legacymsp430.h>

int main(void) {
	volatile int c, i;

	WDTCTL = WDTPW + WDTHOLD; // Stop watchdoc timer
	P1DIR |= 1<<0; // Set P1.0 (red LED) to output
	P1OUT &= ~(1<<0); // Turn LED off

	P1DIR |= 1<<6; // Set P1.6 (green LED) to output
	P1OUT &= ~(1<<6); // Turn LED off

	P1REN |=  1<<3; // Enable pull-up resistor
	P1DIR &= ~(1<<3); // Set P1.3 (left switch) to input
	P1SEL |=  1<<3; // Select push button

	c = 0;
	while (1) {
		// Toggle green LED
		if (c%5 == 0) {
			P1OUT ^= 1<<6; // Toggle P1.6
		}
		// Toggle red LED if switch pressed
		if ((P1IN & 1<<3) == 0) {
			P1OUT ^= 1<<0;
		}
		// Delay
		for (i = 0, c++; i < c; i++);
	}
}

