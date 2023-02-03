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
//	2	D9	(PWM)	METER_AMP
//	3	D8			METER_VOLT
//	4	D7			STATUS_GREEN
//	5	D6	(PWM)	STATUS_RED
//	6	A0 			DRIVE/BREAK
//	7	A1 			MAINS_SWITCH
//	8	A2 			DIR_SWITCH
//	9	A3			LIGHT_SWITCH
//	10	GND

#if BOARD_VERSION == BOARD_V_1_0

	#define STATUS_RED 6
	#define STATUS_GREEN 7

	#define METER_VOLT 8
	#define METER_AMP 9

	#define ANALOG_DRIVE A0

	#define ANALOG_MAINS_SWITCH A1
	#define ANALOG_DIR_SWITCH A2
	#define ANALOG_LIGHT_SWITCH A3


// Print V1.2 extension bus
// 8x2 pins
//
//	1	VCC						2	D2 			INSTUMENT-LIGHT
//	3	A5			LIGHT		4	D3 (PWM)
//	5	A4			DIR			6	D4			Signal
//	7	A3			MAINS		8	D5 (PWM)
//	8	A2			POWER		10	D6 (PWM)	RED-LED
//	11	A1			BREAK		12	D7			GREEN-LED
//	13	A0			DRIVE/BREAK	14	D8			VOLT-METER
//	15	D9 (PWM)	AMP-METER	16	GND

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
	#define ANALOG_BREAK A1
	#define ANALOG_POWER A2

	#define SIGNAL 4

	#define ANALOG_MAINS_SWITCH A3
	#define ANALOG_DIR_SWITCH A4
	#define ANALOG_LIGHT_SWITCH A5

	#define INSTRUMENT_LIGHT 2

// UNIVERSIAL BOARD VERSION 2.1
// 
// BUS 1
// 
// 9x1 pins
//
//  1   +3,3V
//  2   D2 		RED-LED
//  3   D3		GREEN-LED
//  4   D4 		Instrument-light
//  5   D5 		Signal-button
//  6   D6 		Voltmeter-batt
//  7   D7 		Voltmeter-motor
//  8   D8		Amperemeter
//  9   GND
// 
// BUS 2
// 
// 5+4x1 pins
//
//  1   VCC (12V)
//  2   A5		Light-switch
//  3   A4		Mains-switch
//  4	A3 		Direction-switch
//  5   A2 		Power-pot / Light-1-switch
// 
//  1   A1 		Break-pot
//  2   A0 		Drive-pot
//  3   D9		Signal-1-button
//  4   GND

#elif BOARD_VERSION == BOARD_UNIV_V_2_1

	#define A0 10
	#define A1 11
	#define A2 12
	#define A3 13

	#define STATUS_RED 2
	#define STATUS_GREEN 3

	#define METER_VOLT 6
	#define METER_MOTOR_VOLT 7
	#define METER_AMP 8

	// meter maximum input value
	#define METER_VOLT_VALUE 2100
	#define METER_AMP_VALUE 8800
	#define METER_MOTOR_VALUE 2100

	#define ANALOG_DRIVE A0
	#define ANALOG_BREAK A1
	// #define ANALOG_POWER A2 // alternative as second light switch

	#define SIGNAL 5
	#define SIGNAL_1 9

	#define ANALOG_MAINS_SWITCH A4
	#define ANALOG_DIR_SWITCH A3
	#define ANALOG_LIGHT_SWITCH A5
	#define ANALOG_LIGHT_1_SWITCH A2 // alternative as power pot

	#define INSTRUMENT_LIGHT 4

// WIFI BOARD VERSION 2.1
// 
// BUS 1
// 
// 9x1 pins
//
//  1   +3,3V
//  2   IO27	ADC2/7 		RED-LED
//  3   IO26	ADC2/9 		GREEN-LED
//  4   IO25	ADC2/8 		Instrument-light
//  5   IO33	ADC1/5 		Signal-button
//  6   IO32	ADC1/4 		Voltmeter-batt
//  7   IO35	ADC1/7 		Voltmeter-motor
//  8   IO34	ADC1/6 		Amperemeter
//  9   GND
// 
// BUS 2
// 
// 5+4x1 pins
//
//  1   VCC (12V)
//  2   IO4 	ADC2/0 		Light-switch
//  3   IO0		ADC2/1 		Mains-switch
//  4   IO2 	ADC2/2 		Direction-switch
//  5   IO15	ADC2/3 		Power-pot
// 
//  1   IO13	ADC2/4 		Break-pot
//  2   IO12	ADC2/5 		Drive-pot
//  3   IO14	ADC2/6 		Light-1-switch / Signal-1-button
//  4   GND

#elif BOARD_VERSION == BOARD_WIFI_V_2_1

	#define A0 10
	#define A1 11
	#define A2 12
	#define A3 13

	#define STATUS_RED 27
	#define STATUS_GREEN 26

	#define METER_VOLT 32
	#define METER_MOTOR_VOLT 35
	#define METER_AMP 34

	#define ANALOG_DRIVE 12
	#define ANALOG_BREAK 13
	#define ANALOG_POWER 15

	#define SIGNAL 33
	// #define SIGNAL_1 14 // alternative second light switch

	#define ANALOG_MAINS_SWITCH 0

	#define ANALOG_DIR_SWITCH 2
	#define ANALOG_LIGHT_SWITCH 4
	#define ANALOG_LIGHT_1_SWITCH 14 // alternative second signal button

	#define INSTRUMENT_LIGHT 25

#else
	#error "No valid board version selected"
#endif



#endif
