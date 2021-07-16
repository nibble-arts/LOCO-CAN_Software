/*
 * LOCO-CAN Controler Module
 * 
 * @author: Thomas H Winkler
 * @copyright: 2020
 * @lizence: GG0
 */


#include "module.h"
#include "config.h"


#include "simpletimeout.h"
#include "can_com.h"
#include "can_protocol.h"


extern CAN_COM can_com;


void MODULE::begin(void) {

  #ifdef DEBUG
    Serial.println("start controller module");
  #endif
  
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


	// start second analog light switch
	#ifdef ANALOG_LIGHT_1_SWITCH
		_light_1_switch.begin(ANALOG_LIGHT_SWITCH);

		_light_1_switch.learn(LIGHT_1_OFF);
		_light_1_switch.learn(LIGHT_1_LOW);
		_light_1_switch.learn(LIGHT_1_LOW_TRAIN);
		_light_1_switch.learn(LIGHT_1_HIGH_TRAIN);
	#endif

	// ===================================================================
	// start Analog meters
	_meter_volt.begin(METER_VOLT, METER_TYPE_SERVO);

	#ifdef METER_AMP
		_meter_amp.begin(METER_AMP, METER_TYPE_SERVO);
	#endif

	#ifdef METER_MOTOR_VOLT
		_meter_motor.begin(METER_MOTOR_VOLT, METER_TYPE_SERVO);
	#endif


	// ===================================================================
	// INIT SEQUENCE
	// set meters to max
	_meter_volt.set(1000);

	#ifdef METER_AMP
		_meter_amp.set(1000);
	#endif

	#ifdef METER_MOTOR_VOLT
		_meter_motor.set(1000);
	#endif


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

	// reset meters
	_meter_volt.set(0);

	#ifdef METER_AMP
		_meter_amp.set(0);
	#endif

	#ifdef METER_MOTOR_VOLT
		_meter_motor.set(0);
	#endif


	// ===================================================================
	// set controller inactive
	_active = false;

  #ifdef DEBUG
    Serial.println("startup successfull");
  #endif

}


void MODULE::update(void) {

	CAN_MESSAGE message;

	_drive_val = 0;
	_break_val = 0;
	_power_val = 0;


	// RECEIVE DATA
	_receive(message);

	// check for CAN drive connection
	if (!can_com.alive() || _drive_timeout.check()) {
		_status.set(0);
		_active = false;
	}


	// set switches and analog values
	_mains();
	_activate();
	_dir();
	_light();
	_drive_break();


    // *****************
	// switch instrument light if output is present
	#ifdef INSTRUMENT_LIGHT


	#endif
    // *****************


// Serial.print(_active);
// Serial.print(" ");
// Serial.print(_switches.get(), BIN);
// Serial.print(" ");
// Serial.println(_status.get(), BIN);

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
	_collision = false;

	if (filter = can_com.read(&message)) {

		// Serial.println(filter);

		// set _status
		switch (filter) {

			// status
			case  CAN_ID_STATUS:
				_status.set(message.data[0]);
				_drive_timeout.retrigger();
				break;


			// set battery voltage
			case CAN_ID_VOLTAGE:
				_value = char2int(message.data[0], message.data[1]);
				_meter_volt.set(map(_value, 0, 1023, 0, 1000));
				break;

// *****************
// OPTIONAL - depends on the board version
// display motor voltage
#ifdef METER_MOTOR_VOLT
			case CAN_ID_MOTOR_VOLTAGE:
				_value = char2int(message.data[0], message.data[1]);
				_meter_motor.set(map(_value, 0, 1023, 0, 1000));
				break;
#endif
// *****************

// *****************
// OPTIONAL - depends on the board version
// display current
#ifdef METER_AMP

			// set system current
			case CAN_ID_CURRENT:
				_value = char2int(message.data[0], message.data[1]);
				_meter_amp.set(map(_value, 0, 1023, 0, 1000));
				break;
#endif
// *****************

			// check for other drive messages
			case CAN_ID_DRIVE:
				_collision = true;
				break;


// *****************
// OPTIONAL - depends on the board version
// switch instrument light by light message if output is present
#ifdef INSTRUMENT_LIGHT

			// set instrument light
			case CAN_ID_LIGHT:
				digitalWrite(INSTRUMENT_LIGHT, message.data[0] & LIGHT_INSTR);
				break;

#endif
// *****************

		}
	}
}


// ========================================================================
// ACTIVATE
bool MODULE::_activate(void) {

	// foreign drive commands
// ========================================================================
// TODO
// check for other controllers
// only one may be avtive

	if (_collision) {
		_active = false;
	}

	else {

		// no other drive commands found and mains is on
		// set active
		if (_mains_switch.get() > 1) {
			_active = true;
		}

		else {
			_active = false;
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

		// send light
		buffer[0] = _lights.get();


// ****************
// combine light switch with second light switch
// bitwise or combination
#ifdef ANALOG_LIGHT_1_SWITCH
		buffer[0] |= _lights_1.get();
#endif
// ****************

		can_com.send(buffer, 1, CAN_ID_LIGHT);

		// send signal
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


#ifdef ANALOG_LIGHT_1_SWITCH

	switch (_light_1_switch.get()) {

		// light OFF
		case LIGHT_OFF:
			_lights_1.set(0);
			break;

		// light LOW
		case LIGHT_LOW:
			_lights_1.set(0);
			_lights_1.set_flag(LIGHT_MAIN, true);

			_lights_1.set_flag(LIGHT_INSTR, true);
			_lights_1.set_flag(LIGHT_LOW, true);
			break;

		// light LOW + TRAIN
		case LIGHT_LOW_TRAIN:
			_lights_1.set(0);
			_lights_1.set_flag(LIGHT_MAIN, true);

			_lights_1.set_flag(LIGHT_INSTR, true);
			_lights_1.set_flag(LIGHT_LOW, true);
			_lights_1.set_flag(LIGHT_TRAIN, true);
			break;

		// light HIGH + TRAIN
		case LIGHT_HIGH_TRAIN:
			_lights_1.set(0);
			_lights_1.set_flag(LIGHT_MAIN, true);

			_lights_1.set_flag(LIGHT_INSTR, true);
			_lights_1.set_flag(LIGHT_HIGH, true);
			_lights_1.set_flag(LIGHT_TRAIN, true);
			break;

	}
#endif

}


// ========================================================================
// set drive/break
// is drive
void MODULE::_drive_break(void) {

	// only if drive is on
	if (_switches.get_flag(DRIVE_FLAG)) {

		_value = analogRead(ANALOG_DRIVE);

		if (_value > SPEED_MID_HIGH) {

			_drive_val = (uint16_t)map(_value, SPEED_MID_HIGH, ANALOG_VAL_MAX, 0, ANALOG_VAL_MAX);
			_break_val = 0;
		}

		// is break
		if (_value < SPEED_MID_LOW) {

			_break_val = (uint16_t)map(_value, SPEED_MID_LOW, 0, 0, ANALOG_VAL_MAX);
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
		_status_led.flash(STATUS_ERROR_FLASH);
	}


	// ERROR status
	else  if (_status.get_flag(ERROR_FLAG)) {
		_status_led.color(RED);
		_status_led.blink(STATUS_ERROR_BLINK);
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
			_status_led.blink(STATUS_READY_BLINK);
		}

		// zero position error
		if (_status.get_flag(ERROR_FLAG)) {
			_status_led.color(RED);
			_status_led.blink(STATUS_ERROR_BLINK);
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

		_status_led.flash(STATUS_OFF_FLASH);
	}




// show low battery state

	// _status_led.offColor(RED);
	// _status_led.forceBlink(200);

}
