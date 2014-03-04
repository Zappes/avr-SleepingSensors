/*
 * Controller code for a device that reads analog sensor values and sleeps
 * while it isn't used. Check the README at Github for more information.
 *
 * Written by Gregor Ottmann, https://github.com/Zappes
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include "lib/lcd-routines.h"
#include "lib/sensors.h"
#include "lib/sleepcontrol.h"
#include "lib/util.h"

// The number of milliseconds after which the LCD and processor will go
// to sleep.
#define TIME_AWAKE 3000

// The number of milliseconds for which the "Sleep ..." text will be shown
// before the LCD is switched off.
#define TIME_BEFORE_SLEEP 500

// This buffer will be used for formatting strings that are written to
// the LCD.
char buffer[17];

// Yeah, i somehow like the Arduino-like code structure and mimicked it.

/*
 * This function is called once right after the controller starts up. This
 * is where the initialization functions of the different libraries are called.
 */
void setup() {
	lcd_init();
	sensors_init();

	// This one doesn't only set the interrupt handler, it also configures
	// the IO pins used for the wake-up button and for switching power to
	// the LCD backlight. I simply had no idea how to name that one.
	interrupt_init();

	// Switch off the internal LED on pin13/PB7 in order to save power. That
	// probably doesn't help much, but every mA counts. :)
	DDRB |= _BV(PB7);
	PORTB &= ~_BV(PB7);

	// Switch on the LCD and print the greeting line. Actually it doesn't only
	// control the backlight but also the contrast.
	lcd_light_state(1);
	lcd_home();
	lcd_string("Started! ");
}

/*
 * This method is called continouusly, i.e. in a while(1) loop. This is
 * where the exciting stuff happens. Well, "exciting" depends on your
 * point of view and level of experience, I guess.
 */
void loop() {
	// Place the cursor in the second line of the display and output the current
	// sensor values. Note that I didn't bother to translate those values to
	// an actual light level and temperature - I only scaled the light sensor's
	// output so it looked nicer on the display.
	// I use hex codes instead of decimal because it's more 31337.
	lcd_setcursor(0,2);
	int ldrValue = map(getAnalogValue(SEN_LDR_PIN), 0x050, 0x3ff, 0x000, 0xfff);
	int trmValue = getAnalogValue(SEN_TRM_PIN);

	sprintf(buffer, "LDR %03x  TRM %03x", ldrValue, trmValue);
	lcd_string(buffer);

	// Show the sensor readings for some time ...
	_delay_ms(TIME_AWAKE);

	// ... then say that we're sleepy ...
	lcd_home();
	lcd_string("Sleep ...");
	_delay_ms(TIME_BEFORE_SLEEP);

	// ... switch off the LCD and put the processor in deep sleep mode.
	lcd_light_state(0);

	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_mode();

	// When the button is pressed, the program will resume right here after
	// the interrupt handler has been executed. A good moment for reactivating
	// the LCD.
	lcd_home();
	lcd_string("Wake up! ");
	lcd_light_state(1);
}

/*
 * This one doesn't do much. It just calls the two other functions.
 */
int main(void)
{
	setup();

	while(1)
	{
		loop();
	}

	return 0;
}

