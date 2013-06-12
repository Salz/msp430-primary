// toggle LED1 while being in low power mode

#include <msp430.h>
#include <legacymsp430.h>

#define LED1 (1<<0)
#define LED2 (1<<6)

#define BTN  (1<<3)

int main(void) {
	volatile unsigned i;
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

	_BIS_SR(LPM4_bits + GIE); // Enable low power (1uA) and interrupts

	// never reached
	for(;;) {
		P1OUT |= LED2;
		for (i = 0; i < 50000; i++);
		P1OUT &= ~LED2;
		for (i = 0; i < 50000; i++);
	}
}

#pragma vector=PORT1_VECTOR
__interrupt void toggle(void) {
	static int state = 0;
	volatile unsigned i;

	P1IE  &= ~BTN;	// Disable IRQ to avoid bouncing
	P1IFG &= ~BTN;	// Clear Interrupt

	state++;
	// switch statement instructions simplified
	// only toggle changing LEDs, and every state is preceeded by state-1
	switch (state & 3) {
		case 0:
			// turn LED1 and LED2 off
			P1OUT &= ~(LED1|LED2);
			break;
		case 1:
		case 3:
			// turn LED1 on
			P1OUT |= LED1;
			break;
		case 2:
			// turn LED1 off, LED2 on
			P1OUT ^= (LED1|LED2);
			break;
	}

	// Quick'n'dirty
	for (i = 0; i < 35000; i++);
	P1IE  |=  BTN;	// Re-enable interrupt
	P1IFG &= ~BTN;	// Clear Interrupt

	// TODO: better: disable irq and enable after timeout

}

