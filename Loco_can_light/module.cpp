/*
 * LOCO-CAN Voltage/Current Module

 * @author: Thomas H Winkler
 * @copyright: 2020
 * @lizence: GG0
 */


#include "module.h"

#include "can_com.h"
#include "can_protocol.h"


// init extern classes
extern CAN_COM can_com;
extern INTELLILED led;


// init classes
CAN_MESSAGE message;
FLAGS status;



// start module
void MODULE::begin(void) {

	uint8_t ports[] = {LIGHT1, LIGHT2, LIGHT3, LIGHT4, LIGHT5, LIGHT6};

	// start send timing
	_send_timeout.begin(LIGHT_CURRENT_TIME);


	// init light setup in EEPROM
	_settings.begin(&can_com, SOFTWARE_VERSION, MODULE_LIGHT, MODULE_MAX_SETTINGS);


	#ifdef DEBUG
		Serial.println();
		Serial.print("module name: '");
		Serial.print(_settings.name());
		Serial.println("'");

		Serial.println("output settings: ");

		for (_i = 0; _i < 7; _i++) {

			Serial.print(_i);
			Serial.print(" forwards: ");
			Serial.print(_settings.getByte(_i), BIN);

			Serial.print(" backwards: ");
			Serial.println(_settings.getByte(_i + 7), BIN);
		}

	#endif


	// set output ports as LED object
	for (_i=0; _i<7; _i++) {
		_leds[_i].begin(ports[_i]);
		_leds[_i].off();
	}


	// set current class
	_current.begin(C1);
	_current.setResolution(ANALOG_RESOLUTION);
	_current.calibrate(1);


	Serial.println("Light module started");

}


// send values by time settings
void MODULE::update(void) {


	uint8_t size;
	uint8_t data[8];
	uint8_t lights;
	uint16_t current;
	uint16_t uuid;
	uint8_t idx;
	uint16_t filter;

	uint8_t name[MODULE_NAME_LENGTH];

	FLAGS light_out;

	// send current
	if (_send_timeout.update()) {

		current = _current.get();

		// current data
		data[0] = current >> 8;
		data[1] = current & 0xff;

		// send light status to CAN
		send(data, 2, CAN_ID_LIGHT_CURRENT);
	}


	// =================================================0
	// data section
	// check for message
	// set light
	if (filter = can_com.read(&message)) {

// Serial.println(filter, HEX);

		switch (filter) {

			// light data
			case CAN_ID_LIGHT:
				_switches.set(message.data[0]);
				break;

			// loco status data
			case CAN_ID_DRIVE:
				_status.set(message.data[0]);
				break;

		}


		// =================================================
		//
		// REQUEST SECTION
		//
		if (filter == CAN_ID_REQUEST) {


			// global request
			if (message.size == 1) {
				_settings.sendInfoReply(MODULE_LIGHT);
			}

			// addressed request
			else {

				// got request
				uuid = char2int(message.data[0], message.data[1]);

				// check for own uuid
				if (can_com.uuid() == uuid) {

					switch(message.size) {

						// info request
						case 2:
							_settings.sendInfoReply(MODULE_LIGHT);
							break;

						// single value request
						case 3:
							_settings.sendValueReply(message.data[2], 1);
							break;

						// multiple value request
						case 4:
							_settings.sendValueReply(message.data[2], message.data[3]);
							break;
					}
				}
			}
		}


		// =================================================
		//
		// SETUP SECTION
		//
		if (filter == CAN_ID_SETUP) {

			// got setup data
			uuid = char2int(message.data[0], message.data[1]);

			// check for own uuid
			if (can_com.uuid() && uuid) {

				idx = message.id & 0x7F;

				// set name
				if (idx == 0) {

					// collect name data
					for (_i = 0; _i < (message.size - 2); _i++) {
						data[_i] = message.data[_i + 3];
					}

					_settings.readName(data, _i, message.data[2]);
				}

				// set values
				else if (idx > 0 && idx != 0x7F) {
					// write values to eeprom
					_i = 2;
					while (_i < message.size) {
						_settings.setByte(message.data[_i], idx + _i - 3);

						_i++;
					}
				}
			}
		}
	}


	// all lights off
	lights = 0;


// Serial.println(_status.get(), BIN);

	// lights only when mains is on
	if (_status.get_flag(MAINS_FLAG)) {

		// select light settings
		for (_i = 0; _i < 7; _i++) {

			if (_switches.get_flag(_i)) {

				// get backwards light
				// data [7-13]
				if (_status.get_flag(DIR_FLAG)) {
					lights |= _settings.getByte(_i + 7);
				}

				// get forward light
				// data [0-6]
				else {
					lights |= _settings.getByte(_i);
				}

			}
		}
	}


	light_out.set(lights);

	// set light outputs
	for (_i = 0; _i<6; _i++) {
		if (light_out.get_flag(_i)) {
			_leds[_i].on();
		}

		else {
			_leds[_i].off();
		}

		_leds[_i].update();
	}


}



// send data to can
bool MODULE::send(uint8_t* data, uint8_t length, long id) {

	// send data
	// blink led
	led.on();

	can_com.send(data, length, id);

	led.off();
}