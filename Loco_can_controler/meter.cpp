/*
 * LOCO-CAN Analog Meter Class
 * 
 * @author: Thomas H Winkler
 * @copyright: 2020
 * @lizence: GG0
 */

#include "meter.h"


METER::METER(void) {}


void METER::begin(uint8_t port) {
	begin(port, METER_DEFAULT_TYPE);
}


void METER::begin(uint8_t port, uint8_t type) {
	_port = port;
	set_type(type);


	// init by type
	switch(type) {

		case METER_TYPE_ANALOG:

			set_limits(METER_DEFAULT_ANALOG_MIN, METER_DEFAULT_ANALOG_MAX);

			// init analog output
			pinMode(_port, OUTPUT);
			set(METER_DEFAULT_ANALOG_MIN);

			break;

		case METER_TYPE_SERVO:

			set_limits(METER_DEFAULT_SERVO_MIN, METER_DEFAULT_SERVO_MAX);

			// init servo and move to min
			_servo.attach(_port);
			set(_min);

			break;
	}
}


void METER::set_type(uint8_t type) {
	_type = type;
}


void METER::set_limits(uint16_t min, uint16_t max) {
	_min = min;
	_max = max;
}


void METER::set(uint16_t value) {

	uint16_t calc;

	calc = map(value, 0, 1000, _min, _max);

	// set by type
	switch(_type) {

		case METER_TYPE_ANALOG:

			// TODO add speed
			analogWrite(_port, calc);
			break;

		case METER_TYPE_SERVO:

			// TODO add speed
			_servo.write(calc);
			break;
	}
}
