#include "sensors.h"
#include <avr/io.h>

void sensors_init() {
	// the sensor is on pin A0 of the arduino mega -> PF0 of the ATmega2560
	SEN_DIR &= ~((1 << SEN_LDR_BIT) | (1 << SEN_TRM_BIT));

	// see http://bennthomsen.wordpress.com/arduino/peripherals/analogue-input/
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));
	ADMUX |= (1<<REFS0);	//Set Voltage reference to Avcc (5v)
	ADCSRA |= (1<<ADEN);	//Turn on ADC
	ADCSRA |= (1<<ADSC);	//Do an initial conversion
}

int getAnalogValue(uint8_t channel) {
	ADMUX &= 0xE0;							//Clear bits MUX0-4
	ADMUX |= channel&0x07;			//Defines the new ADC channel to be read by setting bits MUX0-2
	ADCSRB = channel&(1<<3);		//Set MUX5
	ADCSRA |= (1<<ADSC);				//Starts a new conversion
	while(ADCSRA & (1<<ADSC));	//Wait until the conversion is done
	return ADCW;								//Returns the ADC value of the chosen channel
}
