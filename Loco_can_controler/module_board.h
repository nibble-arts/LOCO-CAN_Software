/*
 * LOCO-CAN Controler Module board configuration
 * 
 * @author: Thomas H Winkler
 * @copyright: 2020
 * @lizence: GG0
 */


#ifndef MODULE_BOARD_H
#define MODULE_BOARD_H

#include "config.h"


/*
 * The bus connector offers seven IO-Lines depending on the used board
 */

// unsupported lines are set to -1

// BOARD VERSION 1.0
//
//	4x analog in
//	4x digital IO
//	2x PWM
//
// Print V1.0 extension bus
//
// 10x1 pins
//
//	1	VCC
//	2	D9	(PWM)
//	3	D8
//	4	D7
//	5	D6	(PWM)
//	6	A0
//	7	A1
//	8	A2
//	9	A3
//	10	GND

#if BOARD_VERSION == BOARD_V_1_0

	#define STATUS_RED 6
	#define STATUS_GREEN 7

	#define METER_VOLT 8
	#define METER_AMP 9

	#define ANALOG_DRIVE A0
	// #define ANALOG_POWER -1

	#define ANALOG_MAINS_SWITCH A1

	#define ANALOG_DIR_SWITCH A2
	#define ANALOG_LIGHT_SWITCH A3


// Print V1.2 extension bus
// 8x2 pins
//
//	1	VCC			2	D2
//	3	A5			4	D3 (PWM)
//	5	A4			6	D4
//	7	A3			8	D5 (PWM)
//	8	A2			10	D6 (PWM)
//	11	A1			12	D7
//	13	A0			14	D8
//	15	D9 (PWM)	16	GND

// big extension bus version
// 9x2 pins
//  ...
//	17	+12V		18	GND

#elif BOARD_VERSION == BOARD_V_1_2

	#define STATUS_RED 6
	#define STATUS_GREEN 7

	#define METER_VOLT 8
	#define METER_AMP 9

	#define ANALOG_DRIVE A0
	// #define ANALOG_POWER -1

	#define ANALOG_MAINS_SWITCH A1

	#define ANALOG_DIR_SWITCH A2
	#define ANALOG_LIGHT_SWITCH A3

#elif BOARD_VERSION == BOARD_WIFI_V_2_0

	#define A0 10
	#define A1 11
	#define A2 12
	#define A3 13

	#define STATUS_RED 6
	#define STATUS_GREEN 7

	#define METER_VOLT 8
	#define METER_AMP 9

	#define ANALOG_DRIVE A0
	// #define ANALOG_POWER -1

	#define ANALOG_MAINS_SWITCH A1

	#define ANALOG_DIR_SWITCH A2
	#define ANALOG_LIGHT_SWITCH A3

#else
	#error "No valid board version selected"
#endif



#endif
