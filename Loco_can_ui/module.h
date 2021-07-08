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

#include "config.h"
#include "simpletimeout.h"
#include "measure.h"


class MODULE {

	public:
		MODULE(void);
		void update(void);
		void set_idx(uint8_t idx);
	
	private:
		uint8_t _idx;

		long _curr_time;
		long _volt_time;

		uint8_t current(uint8_t*);
		uint8_t voltage(uint8_t*);
		bool send(uint8_t*, uint8_t, long);
		
		MEASURE _c[UI_MAX_CURR];
		MEASURE _v[UI_MAX_VOLT];

		SIMPLETIMEOUT _curr_timeout;
		SIMPLETIMEOUT _volt_timeout;

};

#endif