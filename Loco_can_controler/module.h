/*
 * LOCO-CAN Controller Module header file
 * 
 * @author: Thomas H Winkler
 * @copyright: 2020
 * @lizence: GG0
 */


#ifndef MODULE_H
#define MODULE_H


#include <Servo.h>

#include "config.h"

#include "can_com.h"
#include "intelliled.h"
#include "simpletimeout.h"
#include "flags.h"
#include "AnalogSwitch.h"
#include "meter.h"

// #include "settings.h"


class MODULE {

	public:
		void begin(void);
		void update(void);

	private:
		void _receive(CAN_MESSAGE);
		void _mains(void);
		void _dir(void);
		void _light(void);
		void _led(void);
		
		void _drive_break(void);
		void _send(void);

		bool _activate(void); // activate controler > returns new state

		bool _active;
		uint16_t _value;

		uint16_t _drive_val;
		uint16_t _break_val;
		uint16_t _power_val;

		bool _collision; // drive message collision

		ANALOGSWITCH _mains_switch;
		ANALOGSWITCH _dir_switch;
		ANALOGSWITCH _light_switch;

		#ifdef ANALOG_LIGHT_1_SWITCH
			ANALOGSWITCH _light_1_switch;
			FLAGS _lights_1;
		#endif

		FLAGS _status;
		FLAGS _switches;
		FLAGS _lights;

		FLAGS _light_status; //can light status

		METER _meter_volt;

		#ifdef METER_AMP
			METER _meter_amp;
		#endif

		#ifdef METER_MOTOR_VOLT
			METER _meter_motor;
		#endif

		INTELLILED _status_led;

		SIMPLETIMEOUT _timeout;
		SIMPLETIMEOUT _drive_timeout;
		SIMPLETIMEOUT _heartbeat;

};


#endif