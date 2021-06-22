/*
 * LOCO-CAN current class
 * 
 * @author: Thomas H Winkler
 * @copyright: 2020
 * @lizence: GG0
 */

#include "current.h"
#include <Arduino.h>

/*
 * init current port
 */
CURRENT::CURRENT() {
}


void CURRENT::begin(uint8_t port) {
	_port = port;
	pinMode(port, INPUT);
}

/*
 * get current value
 */
long CURRENT::get(void) {

//TODO calculate value

	return analogRead(_port);
}
