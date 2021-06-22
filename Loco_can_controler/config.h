/*
 * LOCO-CAN module configuration file
 * 
 * @author: Thomas H Winkler
 * @copyright: 2020
 * @lizence: GG0
 */


#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

#include "loco_config.h"


// =====================================
// The main module methods
// are declared in module.h
//
// The board definitions are
// defined in module_board.h
//
// Valid board versions:
//		BOARD_V_1_0
//		BOARD_V_1_2
//		BOARD_V_2_0
// =====================================


// =====================================
//
// select board version
//
// =====================================
#define BOARD_VERSION BOARD_V_1_0
#define SOFTWARE_VERSION 0x0100
#define MODULE_MAX_SETTINGS 23


// =====================================
//
// local definitions
//
// =====================================

// All local definitions are placed here
#define VAL_MAX 1023
#define SPEED_MID_HIGH 582
#define SPEED_MID_LOW 227

// analog switches
#define MAINS_OFF 0
#define MAINS_ON 512
#define MAINS_PUMP 1023

#define DIR_REVERSE 0
#define DIR_MID 512
#define DIR_FORWARD 1023

#define LIGHT_OFF 0
#define LIGHT_LOW 338
#define LIGHT_LOW_TRAIN 680
#define LIGHT_HIGH_TRAIN 1023


// max settings mytes
#define EEPROM_MAX_DATA 14

// =====================================
// include module
#include "module_board.h"
#include "module.h"


#endif
