/*
 * LOCO-CAN Controler Module
 * 
 * @author: Thomas H Winkler
 * @copyright: 2020
 * @lizence: GG0
 */

/*
 * The controler module is for simple units
 * that use a CAN cable connection for controlling
 * the train.
 *
 * For the connection see the module_board.h file.
 */

/*
 * SEND:
 * 7 byte package
 *
 * STATUS
 * byte 0:   7      6      5      4      3      2      1      0
 *         error  ready   stop                 dir   drive  mains
 *
 * DRIVE VALUE: 10-bit value of drive voltage
 * byte 1: drive bit 8-9
 * byte 2: drive bit 0-7
 *
 * POWER VALUE: 10-bit value of drive max power
 * byte 3: power bit 8-9
 * byte 4: power bit 0-7
 *
 * BREAK VALUE: 10-bit value of break intensity
 * byte 5: break bit 8-9
 * byte 6: break bit 0-7
 */

/*
 * RECEIVE:
 * 
 * STATUS
 * byte 0:   7      6      5      4      3      2      1      0
 *         error  ready   stop                 dir   drive  mains
 */


#include "Servo.h"

#include "config.h"

#include "can_com.h"
#include "can_protocol.h"

#include "intelliled.h"
#include "simpletimeout.h"
#include "flags.h"
#include "AnalogSwitch.h"
#include "settings.h"


CAN_COM can_com;

SETTINGS settings;

MODULE module;

void setup() {

	// ===================================================================
	// start basic functions
	Serial.begin(115200);


	// ===================================================================
	// INIT CAN
	Serial.println("Start CAN Controler");

	can_com.begin(CAN_BUS_SPEED); // set CAN speed
	can_com.setLivetime(500); // set live timeout for CAN communication (this module sends heartbeat)


	// register can filters
	can_com.register_filter(CAN_ID_MASK, CAN_ID_LIGHT_CURRENT); // light
	can_com.register_filter(CAN_ID_MASK, CAN_ID_STATUS); // drive status
	can_com.register_filter(CAN_ID_MASK, CAN_ID_DRIVE);	// drive commands from other controllers

	can_com.register_filter(CAN_SETUP_MASK, CAN_ID_REPLY);
	can_com.register_filter(CAN_REPLY_MASK, CAN_ID_REPLY);


	#ifdef DEBUG
		Serial.println();
		Serial.print("Device UUID: ");
		Serial.println(can_com.uuid(), HEX);
	#endif

	// init settings
	settings.begin(can_com.uuid(), SOFTWARE_VERSION, MODULE_CONTROLLER, MODULE_MAX_SETTINGS);


	// start module
	module.begin();
}


void loop() {

	// update module
	module.update();
}
