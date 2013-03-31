// See http://homepages.ius.edu/rwisman/C335/html/Syllabus.htm

#include <msp430.h>
#include <legacymsp430.h>

#define SLEEP (3000U)

#define LED1 (1<<0)
#define LED2 (1<<6)

int main(void) {
	volatile unsigned int i;
	unsigned int c;
	int n;

	WDTCTL = WDTPW + WDTHOLD; // Stop watchdoc timer

	P1DIR |=  LED1; // Set P1.0 (red LED) to output
	P1OUT &= ~LED1; // Turn LED off

	P1DIR |=  LED2; // Set P1.6 (green LED) to output
	P1OUT &= ~LED2; // Turn LED off

	c = 0;
	while (1) {
		// sync: 1 clk green, red off
		P1OUT |=  LED2;
		P1OUT &= ~LED1;
		for (i=0; i<2*SLEEP; i++);

		// output C binary
		for (n = 15; n >= 0; n--) {
			// toggle red LED
			if (c & (1<<n)) {
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

		// increment c
		c++;
	}
	return 0;
}

