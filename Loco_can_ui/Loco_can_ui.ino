/*
 * LOCO-CAN Sensor Module 
 * @author: Thomas H Winkler
 * @copyright: 2020
 * @lizence: GG0
 */

/*
 * The U/I-Module has one current input for the measurement
 * of a DC current up to 50A and four voltage sensor inputs
 * related to GND.
 *
 * The current value can be set to direction sensitive mode,
 * with positive and negative values, or to insensitive mode,
 * where the value always is positive, independent of the
 * current direction.
 *
 *
 * The voltage can be set up to send the absolute voltage
 * in relation to GND-level, or difference values between
 * two inputs.
 * So it is a) possible to get the voltages of two batteries
 * in series plus the over all voltage, or b) the voltage of a
 * motor independent of the direction of operation.
 *
 * a)    GND--[BAT-1]--V1(12V)--[BAT-2]--V2(24V)
 *
 *      V1-GND	> voltage of battery 1
 *		V2-V1	> voltage of battery 2
 *		V2-GND	> over all voltage
 *
 * b)	V1(Motor +) -- V2(Motor -)
 *
 *		V2-V1	> motor voltage
 */

#include "config.h"
#include "module.h"

#include "intelliled.h"



MODULE module;
INTELLILED led(CAN_STATUS_LED);

CAN_COM can_com;



void setup() {

	#ifdef DEBUG
		Serial.begin(115200);
		Serial.println("Start LOCO CAN");
	#endif

	can_com.begin(500E3);

	led.off();

	#ifdef DEBUG
		Serial.print("UUID: ");
		Serial.println(can_com.uuid(), HEX);
	#endif
}


void loop() {

	// update module
	module.update();

	// update led
	led.update();

}
