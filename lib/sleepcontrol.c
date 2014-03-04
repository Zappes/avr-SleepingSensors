#include <avr/io.h>
#include <avr/interrupt.h>

#include "sleepcontrol.h"
#include "lcd-routines.h"

void interrupt_init() {
	cli();

	// configure the button and lcd light control pin
	SC_DIR |= _BV(SC_LCDLIGHT_BIT);	// set the pin for lcd backlight to output
	SC_DIR &= ~_BV(SC_BUTTON_BIT);	// set the button pin to input
	SC_PIN |= _BV(SC_BUTTON_BIT);		// enable the pullup resistor for the button

	// Enable INT0 External Interrupt
	EIMSK |= _BV(SC_BUTTON_INT);

	// Falling-Edge Triggered INT0 - This will depend on if you
	// are using a pullup resistor or a pulldown resistor on your
	// button and port
	EICRA |= _BV(ISC01);

	sei();
}

void lcd_light_state(int state) {
	if(state) {
		SC_PORT |= _BV(SC_LCDLIGHT_BIT);
	}	else {
		SC_PORT &= ~_BV(SC_LCDLIGHT_BIT);

		// switch all pins to low in order to reduce power consumption.
		LCD_PORT = 0x00;
	}
}

/*
 * This routine is called whenever the wake-up button is pushed. The
 * interrupt automatically ends sleep mode, program execution will
 * restart from the next line after the call to sleep mode after this
 * ISR has ended.
 */
ISR(SC_BUTTON_INTV) {
	// don't do anything. we only need to wake up here.
	asm("nop");
}
