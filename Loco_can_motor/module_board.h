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
#define RAMP_DEFAULT 1000
#define RAMP_EMERGENCY 500

#define PWM_RAMP_UPDATE_RATE 20

#define VOLTAGE_ZERO 400 // maximal voltage for null detection in 1/10 V

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

	#define ANALOG_RESOLUTION 10

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

	#define DRIVE_RAMP 500
	#define BREAK_RAMP 200

	#define VOLTAGE_0 A0
	#define VOLTAGE_1 A1

	#define ANALOG_MAX_VAL 1024


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

	#define ANALOG_RESOLUTION 10

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

	#define ANALOG_MAX_VAL 1024


// Print V2.X controller connector
// 5x2 pins
//
//	1	VCC			2	D2
//	3	D9 (PWM)	4	D3
//	5	D6 (PWM)	6	A0
//	7	D7			8	A1
//	8	D8			10	GND


#elif BOARD_VERSION == BOARD_V_2_0 || BOARD_VERSION == BOARD_V_2_1

	#define CAN_STATUS_LED 5

	#define ANALOG_RESOLUTION 10

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

	#define DRIVE_RAMP 20
	#define BREAK_RAMP 10

	#define VOLTAGE_0 A0
	#define VOLTAGE_1 A1

	#define ANALOG_MAX_VAL 1024


// Print V2.X controller connector
// 5x2 pins
//
//	1	VCC			2	D2
//	3	D9 (PWM)	4	D3
//	5	D6 (PWM)	6	A0
//	7	D7			8	A1
//	8	D8			10	GND


#elif BOARD_VERSION == BOARD_V_2_2

	#define CAN_STATUS_LED 5

	#define ANALOG_RESOLUTION 10

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

	#define BATTERY_VOLTAGE_1 A2
	#define BATTERY_VOLTAGE_2 A3

	#define ANALOG_MAX_VAL 1024


#elif BOARD_VERSION == BOARD_UNIV_V_2_X

	#define CAN_STATUS_LED 5

	#define ANALOG_RESOLUTION 10

	// temporary values
	// #define POT_SPEED A2
	// #define SWITCH_DIR A3

	// IO definition
	#define RELAIS_F 2
	#define RELAIS_R 3                                                        
	#define RELAIS_MAIN 4

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

	#define ANALOG_MAX_VAL 1024

// WIFI BOARD VERSION 2.0
// 
// BUS 1
// 
// 9x1 pins
//
//  1   +3,3V
//  2   IO27	ADC2/7 	RELAIS_F
//  3   IO26	ADC2/9 	RELAIS_R
//  4   IO25	ADC2/8 	RELAIS_M
//  5   IO33	ADC1/5
//  6   IO32	ADC1/4 	BREAK_PWM
//  7   IO35	ADC1/7 	VOLT_1
//  8   IO34	ADC1/6 	VOLT_2
//  9   GND
// 
// BUS 2
// 
// 5+4x1 pins
//
//  1   VCC (12V)
//  2   IO4 	ADC2/0
//  3   IO0		ADC2/1
//  4   IO2 	ADC2/2
//  5   IO15	ADC2/3
// 
//  1   IO13	ADC2/4
//  2   IO12	ADC2/5
//  3   IO14	ADC2/6 	DRIVE_PWM
//  4   GND

#if BOARD_VERSION == BOARD_WIFI_V_2_0 || BOARD_VERSION == BOARD_WIFI_V_2_1

    #define CAN_STATUS_LED 5

	#define ANALOG_RESOLUTION 12

    // temporary values
	// #define POT_SPEED A2
	// #define SWITCH_DIR A3

	// IO definition
	#define RELAIS_F 27
	#define RELAIS_R 26                                                         

	#define RELAIS_M 25

	#define HORN -1 
	#define LICHT -1

	#define PWM_DRIVE 14
	#define PWM_BREAK 32

	#define DRIVE_FREQUENCY PWM_RAMP_31KHZ
	#define BREAK_FREQUENCY PWM_RAMP_1KHZ

	#define DRIVE_RAMP 1000
	#define BREAK_RAMP 500

	#define VOLTAGE_0 13
	#define VOLTAGE_1 12

	#define ANALOG_MAX_VAL 4096

#endif
#else
	#error "No valid board version selected"
#endif

#endif
