/*
 * LOCO-CAN LK-motor driver
 * 
 * @author: Thomas H Winkler
 * @copyright: 2020
 * @lizence: GG0
 */


#include "module.h"
#include "config.h"

#include "can_com.h"
#include "can_protocol.h"

#include "intelliled.h"
#include "pwm_ramp.h"
#include "flags.h"

extern CAN_COM can_com;
extern INTELLILED led;

extern FLAGS switches;
extern FLAGS status;


/* *************************************************
 * class construtors
 */
MODULE::MODULE(void) {
}


// start class with user acceleration values
void MODULE::begin(uint16_t ramp_time) {

	pinMode(RELAIS_F, OUTPUT);
	pinMode(RELAIS_R, OUTPUT);

	#ifdef RELAIS_MAIN
		pinMode(RELAIS_MAIN, OUTPUT);
	#endif

	set_ramp(ramp_time);

	_target_speed = 0;
	_current_speed = 0;

	_target_dir = 0;
	_current_dir = 0;
	
	// reset direction outputs
	_clear_dir();

	// start drive PWM
	_pwm_drive.begin(PWM_DRIVE, PWM_RAMP_UPDATE_RATE, DRIVE_FREQUENCY);
	_pwm_drive.set_ramp(DRIVE_RAMP);

	// start break PWM
	_pwm_break.begin(PWM_BREAK, PWM_RAMP_UPDATE_RATE, BREAK_FREQUENCY);
	_pwm_break.set_ramp(BREAK_RAMP);


	// set initial status
	_drive_nulled = false;
	_emergency = false;

	// start drive data and standing and voltage timeout
	_heartbeat_timeout.begin(1000);
	_standing_timeout.begin(1000);
	_voltage_timeout.begin(1000);

	// start voltage
	_voltage.begin(VOLTAGE_0, VOLTAGE_1, ANALOG_RESOLUTION, 30);
	_voltage.set_filter(0.25);
}


/* *************************************************
 * update methods
 */
void MODULE::update(void) {

	uint8_t data[8];
	CAN_MESSAGE message;


	// presume error
	status.set_flag(ERROR_FLAG, false);


	// STATI
	/*
	 * emergency:
	 *		heartbeat timeout
	 * ready:
	 *		status: 
	 */


	// =======================================
	// check if drive is nulled
	// middle position of drive regulator
	//
	// reset emergency
	if (_target_speed == 0) {
		_drive_nulled = true;
	}


	// =======================================
	// check for lost communication
	// set all switches to OFF
	// emergency true

	// replaced by heardbeat

	// if (!can_com.alive()) {
	// 	// switches.set(0);

	// 	// status.set_flag(ERROR_FLAG, true);
	// 	// _emergency = true;
	// 	// _drive_nulled = false;
	// }

	// else {
	// 	status.set_flag(ERROR_FLAG, false);
	// }


	// =======================================
	// set status ready
	status.set_flag(READY_FLAG, ready());


	// error if not nulled
	if (!_drive_nulled && status.get_flag(DRIVE_FLAG)) {
		status.set_flag(ERROR_FLAG, true);
	}


	// =======================================
	// heartbeat timeout > STOP ALL
	if (_heartbeat_timeout.check()) {

		switches.set(0);

		_emergency = true;
		_drive_nulled = false;

		status.set_flag(ERROR_FLAG, true);
	}


	// heartbeat OK
	else {

		// mains on
		if (status.get_flag(MAINS_FLAG)) {

			status.set_flag(ERROR_FLAG, false);
			_emergency = false;


			// send speed
			data[0] = _current_speed >> 8;
			data[1] = _current_speed & 0xFF;
			send(data, 2, CAN_ID_SPEED);

			// send motor voltage
			data[0] = _motor_voltage() >> 8;
			data[1] = _motor_voltage() % 0xFF;
			send(data, 2, CAN_ID_MOTOR_VOLTAGE);

		}

		// mains off
		else {
			status.set_flag(ERROR_FLAG, true);
			_emergency = true;
		}
	}



// Serial.print("switch: ");
// Serial.print(switches.get_flag(MAINS_FLAG), BIN);
// Serial.print(" status: ");
// Serial.print(status.get(), BIN);
// Serial.print(" emerg: ");
// Serial.print(_emergency);
// Serial.print(" V: ");
// Serial.println(_motor_voltage());


	// =======================================
	// =======================================
	// mains on if stopped and mains switch on
	#ifdef RELAIS_MAIN

		if (stopped() || _emergency) {

			// switch on main relais
			if (switches.get_flag(MAINS_FLAG) != 0) {
				_set_mains(true);
			}

			// mains relais OFF
			else {
				_set_mains(false);
				_clear_dir();
			}
		}


	#endif

	// =======================================
	// =======================================
	// status is ready to drive
	if (ready() && !_emergency) {

		// =======================================
		// update direction when drive is stopped
		if (stopped()) {

			_current_dir = _target_dir;

			// set direction
			_set_dir(_current_dir);
		}

		// set drive if break is stopped and nulled and direction is valid
		if (_pwm_break.stopped() && _drive_nulled && _current_dir == _target_dir && _has_direction()) {
			_pwm_drive.pwmWrite(_target_speed);
		}

		// set break if drive is stopped
		if (_pwm_drive.stopped()) {
			_pwm_break.pwmWrite(_target_break);
		}
	}


	// all OFF > drive and break OFF + mains relais OFF
	else {

		_pwm_drive.pwmWrite(0);
		_pwm_break.pwmWrite(0);

		status.set_flag(DRIVE_FLAG, false);

		// _emergency = true;
		_drive_nulled = false;

		// clear directions when stopped and mains off
		if (stopped() && !switches.get_flag(MAINS_FLAG)) {
			_clear_dir();
		}
	}


	// set stop flag
	if (standing()) {
		status.set_flag(STOP_FLAG, true);
	}

	else {
		status.set_flag(STOP_FLAG, false);
	}


	// emergency break
	// if (_emergency) {

	// 	if (get_break() > 250) {
	// 		_emergency = false;
	// 	}

	// 	_pwm_drive.pwmWrite(0);

	// 	if (_pwm_drive.stopped()) {

	// 		// emergency break
	// 		_pwm_break.set_ramp(RAMP_EMERGENCY);
	// 		set_break(255);
	// 	}
	// }

	// else {
	// 	_pwm_break.set_ramp(RAMP_DEFAULT);
	// }



	// update speed/break and get current values
	_current_speed = _pwm_drive.update();
	_current_break = _pwm_break.update();


	// =======================================
	// send status
	data[0] = status.get();
	send(data, 1, CAN_ID_STATUS);

}


// heartbeat => retrigger timeout
void MODULE::heartbeat(void) {
	_heartbeat_timeout.retrigger();
}


/* *************************************************
 * status
 */

// get ready state
bool MODULE::ready(void) {
	return status.get_flag(MAINS_FLAG) & status.get_flag(DRIVE_FLAG) & !status.get_flag(ERROR_FLAG);
}


/* *************************************************
 * speed methods
 */

// ==============================================
// set target speed
void MODULE::set_speed(uint16_t speed) {
	_target_speed = speed;
}


// get current speed
uint16_t MODULE::get_speed(void) {
	return _pwm_drive.pwmRead();
}


// get target speed
uint16_t MODULE::get_target_speed(void) {
	return _pwm_drive.pwmReadTarget();
}


// ==============================================
// set break
void MODULE::set_break(uint16_t break_val) {
	_target_break = break_val;
}


// get current break
uint16_t MODULE::get_break(void) {
	return _pwm_break.pwmRead();
}


// get target break
uint16_t MODULE::get_target_break(void) {
	return _pwm_break.pwmReadTarget();
}


/* *************************************************
 * direction methods
 */
// 	0 = forward
// 	1 = rewards
void MODULE::direction(bool dir) {
	_target_dir = dir;
}

// get current direction
bool MODULE::direction(void) {
	return _current_dir;
}

// set acceleration
void MODULE::set_ramp(uint16_t ramp) {
	_pwm_drive.set_ramp(ramp);
}

// set mains relais
void MODULE::_set_mains(bool stat) {
	digitalWrite(RELAIS_MAIN, stat);
}

// set direction outputs
void MODULE::_set_dir(bool dir) {
	digitalWrite(RELAIS_F, !dir);
	digitalWrite(RELAIS_R, dir);
}

// clear direction outputs
void MODULE::_clear_dir(void) {
	digitalWrite(RELAIS_F, LOW);
	digitalWrite(RELAIS_R, LOW);
}

// check if direction is set
bool MODULE::_has_direction(void) {
	return digitalRead(RELAIS_F) || digitalRead(RELAIS_R);
}


// loco is stopped ?
// pwm drive and break is null
// voltage is under limit
bool MODULE::stopped(void) {
	return _pwm_drive.stopped() && standing() && _pwm_break.stopped();
}


// check if motor is standing
// use timeout to delay status change
bool MODULE::standing(void) {

	// voltage under limit
	if (abs(_motor_voltage()) <= VOLTAGE_ZERO) {

		_voltage_timeout.retrigger();

		if (_standing_timeout.check()) {
			return true;
		}
	}

	else {

		if (_voltage_timeout.check()) {
			_standing_timeout.retrigger();
		}
	}

	return false;
}


int16_t MODULE::_motor_voltage(void) {
	return _voltage.get(MEASURE_VALUE_RELATIVE);
}


// send data to can
bool MODULE::send(uint8_t* data, uint8_t length, long id) {

	// send data
	// blink led
	led.on();
	
	can_com.send(data, length, id);
	delay(10);

	led.off();
}
