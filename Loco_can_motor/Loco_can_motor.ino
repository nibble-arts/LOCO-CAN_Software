/*
 * LOCO-CAN LK-1 motor driver
 * 
 * @author: Thomas H Winkler
 * @copyright: 2020
 * @lizence: GG0
 */

/*
 * The module is designed for the MOSFET motor power unit
 * LK-1 of Mr Habersetzer, that have no reverse protection.
 *
 * Both the motor current and the motor voltage is detected
 * for correct operation. An additional power relay can cut
 * the connection to the motor when in standby.
 *
 */


/*
 * SEND:
 * 
 * STATUS
 * byte 0:   7      6      5      4      3      2      1      0
 *         error  ready   stop                 dir   drive  mains
 */

/*
 * RECEIVE:
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

#include "config.h"
#include "module.h"

#include "intelliled.h"
#include "flags.h"


MODULE module;
INTELLILED led(CAN_STATUS_LED);

CAN_COM can_com;

FLAGS switches;
FLAGS status;


// temp analog input
#define POT A0


void setup() {

	#ifdef DEBUG
		Serial.begin(115200);
		Serial.println("Start LOCO CAN");
	#endif

	// begin CAN communication
	can_com.begin(CAN_BUS_SPEED);
	// can_com.setHeartbeat(HEARTBEAT, CAN_ID_HEARTBEAT);

	#ifdef DEBUG
		Serial.println();
		Serial.print("Device UUID: ");
		Serial.println(can_com.uuid(), HEX);
	#endif


	// register commands to read
	can_com.register_filter(CAN_ID_MASK, CAN_ID_DRIVE);
	can_com.register_filter(CAN_ID_MASK, CAN_ID_LIGHT);
	can_com.register_filter(CAN_ID_MASK, CAN_ID_HEARTBEAT);

	led.off();


	// init module
	module.begin(RAMP_DEFAULT);

	module.set_ramp(1000);
	module.set_speed(127);
	module.set_break(0);

	module.direction(1);


	// start status
	status.begin();
	switches.begin();

}


void loop() {

	CAN_MESSAGE message;

	uint16_t speed_val;
	uint16_t break_val;
	uint16_t power_val;

	uint32_t filter;


	// check for message
	if (filter = can_com.read(&message)) {

		switch(filter) {

			case CAN_ID_DRIVE:

				// remove messy data
				if (message.data[0] != 0) {
					switches.set(message.data[0]);
				}

// Serial.print(filter);
// Serial.print(" ");
// Serial.println(switches.get(), BIN);

				// =======================================
				// set values
				module.direction(switches.get_flag(DIR_FLAG));

				status.set_flag(MAINS_FLAG, switches.get_flag(MAINS_FLAG));
				status.set_flag(DRIVE_FLAG, switches.get_flag(DRIVE_FLAG));

				speed_val = char2int (message.data[1], message.data[2]);
				break_val = char2int (message.data[3], message.data[4]);
				break_val = char2int (message.data[5], message.data[6]);

				module.set_speed(speed_val / 4);
				module.set_break(break_val / 4);

				module.heartbeat();

				break;

			case CAN_ID_HEARTBEAT:
				module.heartbeat();
				break;

			// case CAN_ID_LIGHT:
			// 	Serial.print("Light ");
			// 	break;

			// case CAN_ID_MOTOR_CURRENT:
			// 	Serial.print("Motor Current ");
			// 	break;

			// case CAN_ID_BATT_VOLTAGE:
			// 	Serial.print("Battery voltage ");
			// 	break;
		}
	}

	// update module
	module.update();

	// update led
	led.update();

}
