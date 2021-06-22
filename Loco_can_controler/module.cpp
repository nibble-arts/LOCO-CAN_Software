/*
 * LOCO-CAN Controler Module
 * 
 * @author: Thomas H Winkler
 * @copyright: 2020
 * @lizence: GG0
 */

#include "Servo.h"

#include "config.h"

#include "module.h"
#include "simpletimeout.h"

#include "can_com.h"
#include "can_protocol.h"


extern CAN_COM can_com;


void MODULE::begin(void) {


	// SET TIMEOUTS
	_timeout.begin(200); // drive send
	_drive_timeout.begin(1000); // drive check timeout for activation
	_heartbeat.begin(500); // set heartbeat


	// begin IO
	pinMode(ANALOG_DIR_SWITCH, INPUT);

	// begin flags
	_switches.begin();
	_lights.begin();


	// init status led
	_status_led.begin(STATUS_RED, STATUS_GREEN);

	_status_led.off();
	_status_led.color(GREEN);


	// ===================================================================
	// start analog direction switch 
	_mains_switch.begin(ANALOG_MAINS_SWITCH);

	_mains_switch.learn(MAINS_OFF);
	_mains_switch.learn(MAINS_ON);
	_mains_switch.learn(MAINS_PUMP);

	// start analog direction switch 
	_dir_switch.begin(ANALOG_DIR_SWITCH);

	_dir_switch.learn(DIR_REVERSE);
	_dir_switch.learn(DIR_MID);
	_dir_switch.learn(DIR_FORWARD);

	// start analog light switch
	_light_switch.begin(ANALOG_LIGHT_SWITCH);

	_light_switch.learn(LIGHT_OFF);
	_light_switch.learn(LIGHT_LOW);
	_light_switch.learn(LIGHT_LOW_TRAIN);
	_light_switch.learn(LIGHT_HIGH_TRAIN);


	// ===================================================================
	// start Servo meters
	_meter_volt.attach(METER_VOLT);
	_meter_amp.attach(METER_AMP);

	_meter_volt.write(0);
	_meter_amp.write(0);


	// ===================================================================
	// show startup on status led
	_status_led.color(RED);
	_status_led.on();

	delay(500);

	_status_led.color(YELLOW);
	_status_led.on();
	delay(500);

	_status_led.color(GREEN);
	_status_led.on();
	delay(500);

	_status_led.off();


	// ===================================================================
	// set controller inactive
	_active = false;

}


void MODULE::update(void) {

	CAN_MESSAGE message;

	_drive_val = 0;
	_break_val = 0;
	_power_val = 0;


	// RECEIVE DATA
	_receive(message);

	// check for CAN and drive connection
	if (!can_com.alive() || _drive_timeout.check() || !_active) {
		_status.set(0);
	}
	

	// set switches and analog values
	_mains();
	_dir();
	_light();
	_drive_break();

	// send data to CAN bus
	_send();

	// set status led
	_led();

	// update _status LED
	_status_led.update();
}



// ========================================================================
// RECEIVE CAN DATA
void MODULE::_receive(CAN_MESSAGE message) {

	uint16_t filter;


	if (filter = can_com.read(&message)) {


		// set _status
		switch (filter) {

			// _status
			case  CAN_ID_STATUS:
				_status.set(message.data[0]);
				_drive_timeout.retrigger();
				break;



			// set battery voltage
			case CAN_ID_VOLTAGE:
				_value = char2int(message.data[0], message.data[1]);
				_meter_volt.write(map(_value, 0, 1023, 0, 180));
				break;


			// set system current
			case CAN_ID_CURRENT:
				_value = char2int(message.data[0], message.data[1]);
				_meter_amp.write(map(_value, 0, 1023, 0, 180));
				break;


			// light current
			// case CAN_ID_LIGHT_CURRENT:

			// 	Serial.print("Light current: ");
			// 	Serial.println(char2int(message.data[0], message.data[1]), HEX);
			// 	break;
		}



		// foreign drive commands
	// ========================================================================
	// TODO
	// check for other controllers
	// only one may be avtive



		if (filter == CAN_ID_DRIVE) {
			_active = false;
		}

		// no other drive commands found
		// set active
		else {
			_active = true;
		}
	}
}


// ========================================================================
// SEND DATA
void MODULE::_send(void) {

	uint8_t buffer[8];

	// send data if active
	if (_active && _timeout.update()) {

		// _status value
		buffer[0] = _switches.get();

		// drive value
		buffer[1] = (uint8_t)(_drive_val >> 8);
		buffer[2] = (uint8_t)(_drive_val & 0xFF);

		// power value
		buffer[3] = (uint8_t)(_power_val >> 8);
		buffer[4] = (uint8_t)(_power_val & 0xFF);

		// break value
		buffer[5] = (uint8_t)(_break_val >> 8);
		buffer[6] = (uint8_t)(_break_val & 0xFF);

		can_com.send(buffer, 7, CAN_ID_DRIVE);

		buffer[0] = _lights.get();
		can_com.send(buffer, 1, CAN_ID_LIGHT);
	}


	// ==================================
	// send heartbeat if active
	if (_active && _heartbeat.update()) {
		buffer[0] = 0x00;
		can_com.send(buffer, 1, CAN_ID_HEARTBEAT);
	}
}


// ========================================================================
// SET MAINS SWITCH
// analog tri-state input
// 0V > off
// 2,5V > on
// 5V < on + pump
void MODULE::_mains(void) {

	switch (_mains_switch.get()) {

		// is reverse
		// set dir and drive on
		case 1:
			_switches.set_flag(MAINS_FLAG, LOW);
			_switches.set_flag(PUMP_FLAG, LOW);
			break;

		// mid
		// set drive off
		case 2:
			_switches.set_flag(MAINS_FLAG, HIGH);
			_switches.set_flag(PUMP_FLAG, LOW);
			break;

		// is forward
		// set dir and drive on
		case 3:
			_switches.set_flag(MAINS_FLAG, HIGH);
			_switches.set_flag(PUMP_FLAG, HIGH);
			break;
	}
}


// ========================================================================
// SET DIRECTION
// analog tri-state input
// 0V > forward
// 2,5V > off
// 5V < reverse
void MODULE::_dir(void) {
	switch (_dir_switch.get()) {

		// is reverse
		// set dir and drive on
		case 3:
			_switches.set_flag(DIR_FLAG, HIGH);
			_switches.set_flag(DRIVE_FLAG, HIGH);
			break;

		// mid
		// set drive off
		case 1:
			_switches.set_flag(DRIVE_FLAG, LOW);
			break;

		// is forward
		// set dir and drive on
		case 2:
			_switches.set_flag(DIR_FLAG, LOW);
			_switches.set_flag(DRIVE_FLAG, HIGH);
			break;
	}

}


// ========================================================================
// set _lights
void MODULE::_light(void) {

	switch (_light_switch.get()) {

		// light OFF
		case LIGHT_OFF:
			_lights.set(0);
			break;

		// light LOW
		case LIGHT_LOW:
			_lights.set(0);
			_lights.set_flag(LIGHT_MAIN, true);

			_lights.set_flag(LIGHT_INSTR, true);
			_lights.set_flag(LIGHT_LOW, true);
			break;

		// light LOW + TRAIN
		case LIGHT_LOW_TRAIN:
			_lights.set(0);
			_lights.set_flag(LIGHT_MAIN, true);

			_lights.set_flag(LIGHT_INSTR, true);
			_lights.set_flag(LIGHT_LOW, true);
			_lights.set_flag(LIGHT_TRAIN, true);
			break;

		// light HIGH + TRAIN
		case LIGHT_HIGH_TRAIN:
			_lights.set(0);
			_lights.set_flag(LIGHT_MAIN, true);

			_lights.set_flag(LIGHT_INSTR, true);
			_lights.set_flag(LIGHT_HIGH, true);
			_lights.set_flag(LIGHT_TRAIN, true);
			break;

	}
}


// ========================================================================
// set drive/break
// is drive
void MODULE::_drive_break(void) {

	// only if drive is on
	if (_switches.get_flag(DRIVE_FLAG)) {

		_value = analogRead(ANALOG_DRIVE);

		if (_value > SPEED_MID_HIGH) {

			_drive_val = (uint16_t)map(_value, SPEED_MID_HIGH, VAL_MAX, 0, VAL_MAX);
			_break_val = 0;
		}

		// is break
		if (_value < SPEED_MID_LOW) {

			_break_val = (uint16_t)map(_value, SPEED_MID_LOW, 0, 0, VAL_MAX);
			_drive_val = 0;
		}

	}

	else {
		_drive_val = 0;
		_break_val = 0;
		_power_val = 0;
	}
}


// ==================================
// STATUS LED
// no CAN connection => flash red (1)
void MODULE::_led() {

	// assume no error
	_status_led.color(GREEN);


	// CAN is dead
	if (!can_com.alive()) {
		_status_led.color(RED);
		_status_led.flash(200);
	}


	// MAINS is on
	else if (_status.get_flag(MAINS_FLAG)) {


		// ready to drive
		if (_status.get_flag(DRIVE_FLAG) && !_status.get_flag(ERROR_FLAG)) {

			// standing (5)
			if (_status.get_flag(STOP_FLAG)) {
				_status_led.color(YELLOW);
			}

			// driving (6)
			else {
				_status_led.color(GREEN);
			}

			_status_led.on();
		}

		// drive not ready (3)
		else {
			_status_led.color(YELLOW);
			_status_led.blink(500);
		}

		// zero position error
		if (_status.get_flag(ERROR_FLAG)) {
			_status_led.color(RED);
			_status_led.blink(500);
		}
	}


	// MAINS is off (3)
	else {

		// off but active
		if (_active) {
			_status_led.color(YELLOW);
		}

		// off and inactive
		// other controller is active
		else {
			_status_led.color(RED);
		}

		_status_led.flash(2000);
	}




// show low battery state

	// _status_led.offColor(RED);
	// _status_led.forceBlink(200);

}