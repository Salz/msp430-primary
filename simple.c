// See http://homepages.ius.edu/rwisman/C335/html/Syllabus.htm

#include <msp430.h>
#include <legacymsp430.h>

#define LED1 (1<<0)
#define LED2 (1<<6)

#define BTN  (1<<3)
int main(void) {
	volatile int c, i;

	WDTCTL = WDTPW + WDTHOLD; // Stop watchdoc timer
	P1DIR |=  LED1; // Set P1.0 (red LED) to output
	P1OUT &= ~LED1; // Turn LED off

	P1DIR |=  LED2; // Set P1.6 (green LED) to output
	P1OUT &= ~LED2; // Turn LED off

	P1REN |=  BTN; // Enable pull-up resistor
	P1DIR &= ~BTN; // Set P1.3 (left switch) to input
	P1SEL |=  BTN; // Select push button

	c = 0;
	while (1) {
		// Toggle green LED
		if (c%5 == 0) {
			P1OUT ^= LED2; // Toggle P1.6
		}
		// Toggle red LED if switch pressed
		if ((P1IN & BTN) == 0) {
			P1OUT ^= LED1;
		}
		// Delay
		for (i = 0, c++; i < c; i++);
	}
}

