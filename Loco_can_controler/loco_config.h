/*
 * LOCO-CAN global setup file
 * 
 * @author: Thomas H Winkler
 * @copyright: 2020
 * @lizence: GG0
 */

// =====================================
// LIBRARIES
//
// https://github.com/ricaun/ArduinoUniqueID
// https://github.com/mrbio/Arduino-rokkit-hash
// https://github.com/Chris--A/EEWrap
// =====================================


#ifndef LOCO_CONFIG_H
#define LOCO_CONFIG_H


// =====================================
//
// GLOBAL DEFINITIONS
//
// =====================================

// uncommend to get Serial debug information 
#define DEBUG

// convert bytes to a 16/32 bit integer
#define char2int(MSB, LSB) (uint16_t)(((uint8_t) MSB & 0xFF) << 8 | ((int8_t) LSB & 0xFF))
#define char2long(MSB, LSB, MSB1, LSB1) (((uint32_t) ((uint8_t) MSB)) & 0xFF) << 24 | (((uint32_t) ((uint8_t) LSB)) & 0xFF) << 16 | (((uint32_t) ((uint8_t) MSB1)) & 0xFF) << 8 | (((int8_t) LSB1) & 0xFF)


// =====================================
//
// versions definition
//
// =====================================

// V1.0
#define BOARD_V_1_0 1

// V1.2
#define BOARD_V_1_2 2

// V2.0
#define BOARD_V_2_0 3

// WIFI V2.1
#define BOARD_WIFI_V_2_1 4

// UNIVERSIAL V2.1
#define BOARD_UNIV_V_2_1 5


// =====================================
// Global settings
#define RED INTELLILED_RED
#define GREEN INTELLILED_GREEN
#define YELLOW INTELLILED_YELLOW

#define MODULE_NAME_LENGTH 15

#define HEARTBEAT 500

// =====================================
// setup data in EEPROM
//
// The module setup data is stored in the EEPROM usind
// the EEWrap library. The data struct must contain:
//   uint16_a uuid
//
// uuid must be set to the mcu-uuid, to indicate, that
// valid data was stored.


// =====================================
// CAN identifier definition 0x000 t0 0x7FF (11bit)
// The LSB of ID is the device number (0-F)

// 0xNMO	N=0		reset
//			N=1-6	data type
//			N=7		setup data
//			M 		subtype
//			o 		module ID 		defined when module is registered


// =====================================
//
// MODULE DECLARATION
//
// =====================================

// =====================================
//
// INPUT MODULES

// CABLE CONTROLLER
#define MODULE_CONTROLLER 0x10



// WIFI CONTROLLER
#define MODULE_WIFI 0x11


// =====================================
//
// SENSOR MODULES
#define MODULE_SENSOR 0x20


// =====================================
//
// ACTUATOR MODULES

// MOTOR DRIVER
#define MODULE_MOTOR 0x30


// LIGHT MODULE
#define MODULE_LIGHT 0x31


// =====================================
//
// DRIVE DATA
//
// =====================================

/*
 * 7 byte package
 *
 * STATUS
 * byte 0:   7      6      5      4      3      2      1      0
 *         error  ready   stop   curr   volt   dir   drive  mains
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



#define ERROR_FLAG 7
#define READY_FLAG 6
#define STOP_FLAG 5

#define PUMP_FLAG 3

#define DIR_FLAG 2
#define DRIVE_FLAG 1
#define MAINS_FLAG 0


// =====================================
//
// LIGHT DATA
//
// =====================================

/*
 * 1 byte package
 *
 * LIGHT_STATUS
 * byte 0:   7      6      5      4      3      2      1      0
 *         	main  train   cab   instr   back    high   low   posit
 *
 * main:	main light switch
 * train:	train lights
 * cab:		cabine light
 * instr:	instrument light
 * back:	back light
 * high:	bright spot light
 * low:		low spot light
 * posit:	position light
 */

#define LIGHT_MAIN 7
#define LIGHT_TRAIN 6
#define LIGHT_CAB 5
#define LIGHT_INSTR 4
#define LIGHT_BACK 3
#define LIGHT_HIGH 2
#define LIGHT_LOW 1
#define LIGHT_POSIT 0


// =====================================
//
// SIGNAL DATA
//
// =====================================

/*
 * 1 byte package
 *
 * SIGNAL STATUS
 * byte 0:   7      6      5      4      3      2      1      0
 *                                             bell   low   high
 *
 * high:    hight frequence signal
 * low:     low frequence signal
 * bell:    signal bell
 */

#define SIGNAL_HIGH 0
#define SIGNAL_LOW 1
#define SIGNAL_BELL 2


// ==================================
//
// ATMEL ATMEGA8 & 168/328 / ARDUINO
//
// ==================================

//                  +-\/-+
//            PC6  1|    |28  PC5 (AI 5)
//      (D 0) PD0  2|    |27  PC4 (AI 4)
//      (D 1) PD1  3|    |26  PC3 (AI 3)
//      (D 2) PD2  4|    |25  PC2 (AI 2)
// PWM+ (D 3) PD3  5|    |24  PC1 (AI 1)
//      (D 4) PD4  6|    |23  PC0 (AI 0)
//            VCC  7|    |22  GND
//            GND  8|    |21  AREF
//            PB6  9|    |20  AVCC
//            PB7 10|    |19  PB5 (D 13)
// PWM+ (D 5) PD5 11|    |18  PB4 (D 12)
// PWM+ (D 6) PD6 12|    |17  PB3 (D 11) PWM
//      (D 7) PD7 13|    |16  PB2 (D 10) PWM
//      (D 8) PB0 14|    |15  PB1 (D 9) PWM
//                  +----+


// ==================================
//
// Microchip MCP2515 wiring
//
// ==================================

// MCP2515        Atmega328
//   VCC             5V
//   GND             GND
//   SCK             SCK
//   SO              MISO
//   SI              MOSI
//   CS              10
//   INT             2  (optional)
//
// Espressif ESP32 wiring
//
// CAN-trans        ESP32
//   3V3             3V3
//   GND             GND
//   CTX              5
//   CRX              4


// ==================================
//
// Print V1.0 extension bus
//
// ==================================

// 10x1 PIN (2,54mm Raster)

// 1   VCC
// 2   D9
// 3   D8
// 4   D7
// 5   D6
// 6   A0
// 7   A1
// 8   A2
// 9   A3
// 10  GND

//  ICP-Connector
// 4x1 PIN (2,54mm Raster)
// Mitte: 1200/600

// 1   VCC
// 2   TX
// 3   RX
// 4   DTR (patch) original GND
// 4a  GND (patch)

// CAN-Connector JST-XH 2,5mm Raster
// 1   VCC
// 2   CAN-H
// 3   CAN-L
// 4   GND

// ==================================
//
// Print V1.2 extension bus
//
// ==================================

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

// ICP-Connector
// 6x1 PIN (2,54mm Raster)
// Mitte: 625/125

// 1   DTR
// 2   TX
// 3   RX
// 4   VCC
// 5   CTS
// 6   GND

// CAN-Connector JST-XH 2,5mm Raster
// 1   VCC
// 2   CAN-H
// 3   CAN-L
// 4   GND

// ==================================
//
// Print V2.x
//
// ==================================

// The version 2 is an integraded board wirth MCU, CAN-bus
// and function hardware in one without an extension bus.


#endif