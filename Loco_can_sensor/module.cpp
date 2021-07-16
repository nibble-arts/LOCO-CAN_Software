/*
 * LOCO-CAN Voltage/Current Module

 * @author: Thomas H Winkler
 * @copyright: 2020
 * @lizence: GG0
 */


#include <Arduino.h>
#include "config.h"
#include "module.h"

#include "intelliled.h"
#include "simpletimeout.h"


// Module module;

extern CAN_COM can_com;
extern INTELLILED led;


/*
 * init voltage/current module class
 */
MODULE::MODULE(void) {

	// reset idx
	_idx = 0x3;

	uint8_t i;

	uint8_t _c_port[] = {C1};
	uint8_t _v_port[] = {V1, V2, V3, V4, V5, V6};

	// set current ports
	for (i = 0; i < UI_MAX_CURR; i++) {
		_c[i].begin(_c_port[i], ANALOG_RESOLUTION, 1);
	}

	// set voltage ports
	for (i = 0; i < UI_MAX_VOLT; i++) {
		_v[i].begin(_v_port[i], ANALOG_RESOLUTION, 1);
	}

	// set value send timing
	_curr_time = 0;
	_volt_time = 0;

	_curr_timeout.begin(CURRENT_TIME);
	_volt_timeout.begin(VOLTAGE_TIME);
}


// send values by time settings
void MODULE::update(void) {

	long time;

	uint8_t size;

	uint8_t curr[UI_MAX_CURR];
	uint8_t volt[UI_MAX_VOLT];


	// get time
	time = millis();


	// send current
	if (_curr_timeout.update()) {

		// send to CAN
		current(curr);
		send(curr, UI_MAX_CURR, CAN_ID_MOTOR_CURRENT);
	}

	// send voltage
	if (_volt_timeout.update()) {

		// send to CAN
		voltage(volt);
		send(volt, UI_MAX_VOLT, CAN_ID_BATT_VOLTAGE);

	}


	// check for message to setup
	// if (size = can_com.available()) {
	// 	can_com.read(size);
	// }
}


// set module idx
void MODULE::set_idx(uint8_t idx) {
	_idx = idx;
}


// get current data
// restrict to 8 bit
uint8_t MODULE::current(uint8_t* c) {

	for (uint8_t i = 0; i < UI_MAX_CURR; i++) {
		c[i] = _c[i].get() >> (ANALOG_RESOLUTION - 8);
	}

	return sizeof(c);
}


// get voltage data
// restrict to 8 bit
uint8_t MODULE::voltage(uint8_t* v) {

	for (uint8_t i = 0; i < UI_MAX_VOLT; i++) {
		v[i] = _v[i].get() >> (ANALOG_RESOLUTION - 8);
	}

	return sizeof(v);
}


// send data to can
bool MODULE::send(uint8_t* data, uint8_t length, long id) {

	// send data
	// blink led
	led.on();

	can_com.send(data, length, id);

	led.off();
}

