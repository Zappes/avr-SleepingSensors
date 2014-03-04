/*
 * Function related to entering and leaving sleep mode.
 *
 * Sleep mode is entered automatically some time after a sensor reading hase
 * been displayed. Waking up is forced by pressing a button which creates
 * an interrupt that ends sleep mode. A bit like throwing a cat into the bed
 * a person is sleeping in. Less scratchy, perhaps. The internal pullup for
 * the button pin is active so we don't need an additional external resistor.
 *
 * The button must be connected to a pin that can actually be used for an
 * external interrupt. PD3:0 are the candidates on the ATmega2560.
 *
 * In addition to making the controller sleep, the backlight of the LCD is
 * switched off and the contrast pin is detached from GND in order to prevent
 * current from leaking. This feature is controlled by a digital output pin
 * that's connected to a transistor that switches GND for the LCD backlight
 * and the contrast potentiometer.
 *
 * Both the button and the pin that controls the transistor are connected
 * to the same port in order to keep the code a bit simpler.
 */
#ifndef SLEEPCONTROL_H
#define SLEEPCONTROL_H

#define SC_PORT					PORTD			// The port to which the wake-up button and the power
																	// control pin are connected.
#define SC_DIR					DDRD			// The data direction register for that port.
#define SC_PIN					PIND			// The pin register for that port. Needed for configuring
																	// the internal pull-up resistor.
#define SC_LCDLIGHT_BIT PD0				// The pin for light control.
#define SC_BUTTON_BIT 	PD1				// The actual pin to which the wake-up button is connected.
#define SC_BUTTON_INT		INT1			// The interrupt connected to the button's pin.
#define SC_BUTTON_INTV	INT1_vect	// The interrupt vector for the button's interrupt.

/*
 * Enables the interrupt for button changes, sets data direction for the IO registers
 * and activates the internal pull-up for the button.
 */
void interrupt_init();

/*
 * Switches the backlight and contrast for the LCD on (1) or off (0).
 */
void lcd_light_state(int state);

#endif
