/*
 * Functions for initializing and accessing the analog sensors connected to the
 * controller.
 */
#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>

/*
 * Change these if you want to use different pins for the sensors. The settings below
 * assume that A0/A1 on the Arduino Mega are used which map to PF0/PF1 on the F-port
 * of the ATmega2560.
 *
 * To find out which pins on the controller correspond to certain arduino pins, have
 * a look at the diagrams posted here:
 *
 * http://forum.arduino.cc/index.php/topic,146315.0.html
 * http://forum.arduino.cc/index.php/topic,146511.0.html
 *
 * Those diagrams are as useful as they are pretty, aren't they?
 */
#define SEN_DIR DDRF
#define SEN_LDR_PIN PF0				// The pin where the light sensor is attached.
#define SEN_LDR_BIT DDF0			// The bit used for setting the IO mode of that pin
#define SEN_TRM_PIN PF1				// The pin where the light sensor is attached.
#define SEN_TRM_BIT DDF1			// The bit used for setting the IO mode of that pin

/*
 * Sets up IO pin directions and initializes the ADC so analog values can be read.
 */
void	sensors_init();

/*
 * Reads an analog value from an ADC channel.
 *
 * @param channel This is the pin from which you want to read a value. Use either
 *                SEN_LDR_PIN or SEN_TRM_PIN as argument value.
 */
int getAnalogValue(uint8_t channel);

#endif
