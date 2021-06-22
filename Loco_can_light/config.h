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
// #include "can_protocol.h"

#define VERSION 0.9.0

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
#define BOARD_VERSION BOARD_V_2_0
#define SOFTWARE_VERSION 0x0100


// =====================================
//
// local definitions
//
// =====================================

// All local definitions are placed here
#define MODULE_VERSION 1.0

// value send interval ms
#define LIGHT_CURRENT_TIME 100

// max settings bytes
#define EEPROM_MAX_DATA 14


// =====================================
// include module
#include "module_board.h"
#include "module.h"


#endif
