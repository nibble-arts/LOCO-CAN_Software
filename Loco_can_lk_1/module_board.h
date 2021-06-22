/*
 * LOCO-CAN Voltage/Current Module board configuration
 * 
 * @author: Thomas H Winkler
 * @copyright: 2020
 * @lizence: GG0
 */


#ifndef MODULE_UI_BOARD_H
#define MODULE_UI_BOARD_H

#include "config.h"


/*
 * default accelaration and deceleration values
 */


// max PWM speed value
// #define PWM_MAX_VAL 255

// default ramp time (0 to max) and update rate (ms)
#define RAMP_DEFAULT 2000
#define RAMP_EMERGENCY 1000

#define PWM_RAMP_UPDATE_RATE 20

#define VOLTAGE_ZERO 500 // maximal voltage for null detection in mV

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
//	2	D9	(PWM)	PWM_DRIVE
//	3	D8			RELAIS_R
//	4	D7			RELAIS_F
//	5	D6	(PWM)	PWM_BREAK
//	6	A0
//	7	A1
//	8	A2
//	9	A3
//	10	GND

#if BOARD_VERSION == BOARD_V_1_0

	#define CAN_STATUS_LED 5

	// temporary values
	// #define POT_SPEED A2
	// #define SWITCH_DIR A3

	// IO definition
	#define RELAIS_F 7
	#define RELAIS_R 8
	// #define RELAIS_R 8

	#define HORN -1
	#define LICHT -1

	#define PWM_DRIVE 9
	#define PWM_BREAK 6

	#define DRIVE_FREQUENCY PWM_RAMP_31KHZ
	#define BREAK_FREQUENCY PWM_RAMP_1KHZ

	#define DRIVE_RAMP 1000
	#define BREAK_RAMP 500

	#define VOLTAGE_0 A0
	#define VOLTAGE_1 A1

	#define VOLT_MAX_VAL 1024


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

	#define CAN_STATUS_LED 8

	// temporary values
	// #define POT_SPEED A2
	// #define SWITCH_DIR A3

	// IO definition
	#define RELAIS_F 2
	#define RELAIS_R 3
	#define RELAIS_EXT 4

	#define HORN 5
	#define LICHT 7

	#define PWM_DRIVE 9
	#define PWM_BREAK 6

	#define DRIVE_FREQUENCY PWM_RAMP_31KHZ
	#define BREAK_FREQUENCY PWM_RAMP_1KHZ

	#define DRIVE_RAMP 1000
	#define BREAK_RAMP 1000

	#define VOLTAGE_0 A0
	#define VOLTAGE_1 A1

	#define VOLT_MAX_VAL 1024


// Print V2.X controller connector
// 5x2 pins
//
//	1	VCC			2	D2
//	3	D9 (PWM)	4	D3
//	5	D6 (PWM)	6	A0
//	7	D7			8	A1
//	8	D8			10	GND


#elif BOARD_VERSION == BOARD_V_2_0
	#define CAN_STATUS_LED 5

	// temporary values
	// #define POT_SPEED A2
	// #define SWITCH_DIR A3

	// IO definition
	#define RELAIS_F 7
	#define RELAIS_R 8                                                          
	// #define RELAIS_R 8

	#define HORN -1 
	#define LICHT -1

	#define PWM_DRIVE 9
	#define PWM_BREAK 6

	#define DRIVE_FREQUENCY PWM_RAMP_31KHZ
	#define BREAK_FREQUENCY PWM_RAMP_1KHZ

	#define DRIVE_RAMP 1000
	#define BREAK_RAMP 500

	#define VOLTAGE_0 A0
	#define VOLTAGE_1 A1

	#define VOLT_MAX_VAL 1024

#else
	#error "No valid board version selected"
#endif

#endif
