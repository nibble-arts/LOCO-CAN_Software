/*
 * LOCO-CAN Voltage/Current Module configuration
 * 
 * @author: Thomas H Winkler
 * @copyright: 2020
 * @lizence: GG0
 */

#ifndef MODULE_H
#define MODULE_H

#include <Arduino.h>
#include <EEPROM.h>

#include "config.h"

#include "simpletimeout.h"
#include "flags.h"
#include "intelliled.h"
#include "settings.h"


class MODULE {

	public:
		void begin(void);
		void update(void);
	
	private:

		bool send(uint8_t*, uint8_t, long);

		uint8_t _i;
		
		SETTINGS _settings;
		FLAGS _status;
		FLAGS _switches;

		SIMPLETIMEOUT _send_timeout;

		INTELLILED _leds[6];
};

#endif