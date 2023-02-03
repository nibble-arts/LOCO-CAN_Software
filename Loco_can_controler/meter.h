/*
 * LOCO-CAN Analog Meter Class
 * 
 * @author: Thomas H Winkler
 * @copyright: 2020
 * @lizence: GG0
 */

#ifndef METER_H
#define METER_H


#include <Servo.h>
#include <Arduino.h>


#define METER_TYPE_SERVO 0
#define METER_TYPE_ANALOG 1 // only possible on PWM outputs

#define METER_DEFAULT_TYPE METER_TYPE_SERVO

#define METER_DEFAULT_ANALOG_MIN 0
#define METER_DEFAULT_ANALOG_MAX 1024

#define METER_DEFAULT_SERVO_MIN 0
#define METER_DEFAULT_SERVO_MAX 180

#define METER_DEFAULT_MIN_VALUE 0
#define METER_DEFAULT_MAX_VALUE 1000


class METER {

	public:
		METER(void);

		void begin(uint8_t port); // start meter on port
		void begin(uint8_t port, uint8_t type); // start meter on port with type

		void set_type(uint8_t type); // set meter type to analog or servo
		void set_limits(uint16_t min, uint16_t max); // set min, max value limits
		void set_value_limits(uint16_t, uint16_t); // set min max input value

		void set(uint16_t value); // set meter to value in promille (0-1000)

	private:
		uint8_t _port;
		uint8_t _type;
		uint16_t _val_min;
		uint16_t _val_max;

		// min and max values
		// TODO can be set via configuration
		uint16_t _min;
		uint16_t _max;

		Servo _servo;
};

#endif