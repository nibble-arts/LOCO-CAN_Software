/*
 * LOCO-CAN LK-motor driver header file
 * 
 * @author: Thomas H Winkler
 * @copyright: 2020
 * @lizence: GG0
 */

// LOCO - LK-1 pinning		Board V2
//
// LOCO-port	LK-1 function		LK-1 pin
//	2	D2			Relais 1			5
//	4	D3			Relais 2			6
//	6	D4 (ext. Relais)
//	8	D5			Light				8
//	10	D6		  	Drive (PWM)			4
//	12	D7 (CAN-Status)
//	14	D8			Horn				7
//	15  D9		  	Break (PWM)			3
//
//	16	GND			GND					1,2
//	17	+12Volt		+12Volt				9
//	18	GND 

/*
 * MODULE_LK_1 class
 * 		create class with default acceleration an deceleration values
 * MODULE_LK_1(acc, dec);
 *		create class with user defined values for acc. and dec.
 *		the values can be change usind set_acc / set_dec
 */

#ifndef MODULE_LK_1_H
#define MODULE_LK_1_H

#include "config.h"
#include "simpletimeout.h"
#include "pwm_ramp.h"
#include "measure.h"


class MODULE {

	public:
		MODULE(void);

		void begin(uint16_t ramp_time);

		void heartbeat(void);

		void set_ramp(uint16_t ramp);

		void direction(bool dir);
		bool direction(void);

		void set_speed(uint16_t speed);
		void set_break(uint16_t break_val);

		uint16_t get_speed(void);
		uint16_t get_target_speed(void);

		uint16_t get_break(void);
		uint16_t get_target_break(void);

		void update(void);
		bool ready(void);

		bool send(uint8_t*, uint8_t, long);


	private:
		uint16_t _target_speed;
		uint16_t _current_speed;

		uint16_t _target_break;
		uint16_t _current_break;

		bool _target_dir;
		bool _current_dir;

		uint16_t _ramp_time;
		uint8_t _status;

		void init(void);
		void ramp(void);
		bool stopped(void); // all standing and switched off
		bool standing(void); // not driving
		int16_t _motor_voltage(void);

		void _set_mains(bool); // set mains relais
		void _set_dir(bool); // set direction
		void _clear_dir(void); // clear all directions
		bool _has_direction(void); // check if direction is set

		bool _drive_nulled;
		bool _emergency;

		SIMPLETIMEOUT _heartbeat_timeout;
		SIMPLETIMEOUT _standing_timeout;
		SIMPLETIMEOUT _voltage_timeout;

		PWM_RAMP _pwm_drive;
		PWM_RAMP _pwm_break;

		MEASURE _voltage;

		#if defined(BATTERY_VOLTAGE_1) && defined(BATTERY_VOLTAGE_2)
			MEASURE _batt_volt_1;
			MEASURE _batt_volt_2;
		#endif
};

#endif