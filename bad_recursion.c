#include <msp430.h>

#define LED1 (1<<0)
void blink();

int main() {
	WDTCTL = WDTPW | WDTHOLD;

	P1OUT &= ~LED1;
	P1DIR |= LED1;

	blink();
	return 0;
}

// gcc -Os does tail recursion, so this function does not actually overflow
// Try compiling with -O0 or with the last comment removed.
void blink() {
	volatile unsigned i;

	P1OUT ^= LED1;
	for(i = 0; i < 3000; i++);
	blink();

	//for(i = 0; i < 3000; i++);
}
