/*
 * LOCO-CAN Light Module
 * 
 * @author: Thomas H Winkler
 * @copyright: 2020
 * @lizence: GG0
 */

/* The light module is designed to switch up to
 * six light outputs according to the light mode.
 * The light modes are declared in the loco_config.h
 * file.
 *
 * Each outputs can be assigned to the seven light modes.
 *
 * The current of all lights is detected and used for
 * short circuit protection.
 */


// =====================================
//
// DATA INDEX MAPPING
//
// =====================================

// byte			content
// --------------------------
// dir = 0
//  0		forward_light 1
//  1		forward_light 2
//  2		forward_light 3
//  3		forward_light 4
//  4		forward_light 5
//  5		forward_light 6
//  6		forward_light 7
//
// dir = 1
//  7		backward_light 1
//  8		backward_light 2
//  9		backward_light 3
//  10		backward_light 4
//  11		backward_light 5
//  12		backward_light 6
//  13		backward_light 7



#include "RokkitHash.h"

#include "config.h"
#include "can_com.h"
// #include "can_protocol.h"

#include "intelliled.h"
// #include "simpletimeout.h"


MODULE module;
INTELLILED led(CAN_STATUS_LED);

CAN_COM can_com;



void setup() {

	#ifdef DEBUG
		Serial.begin(115200);
		Serial.println("Start Light-CAN");
	#endif

	can_com.begin(500E3);

	can_com.register_filter(CAN_ID_MASK, CAN_ID_LIGHT);
	can_com.register_filter(CAN_ID_MASK, CAN_ID_DRIVE);
	
	can_com.register_filter(CAN_REQUEST_MASK, CAN_ID_REQUEST);
	can_com.register_filter(CAN_SETUP_MASK, CAN_ID_SETUP);

	led.off();

	#ifdef DEBUG
		Serial.println();
		Serial.print("Device UUID: ");
		Serial.println(can_com.uuid(), HEX);
	#endif

	module.begin();

}


void loop() {

	// update module
	module.update();

	// update led
	led.update();

}
