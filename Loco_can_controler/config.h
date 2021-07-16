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
#include "can_protocol.h"
#include "can_com.h"


// =====================================
// The main module methods
// are declared in module.h
//
// The board definitions are
// defined in module_board.h
//
// Valid board versions:
// 
#define BOARD_V_1_0 1 // V1.0
#define BOARD_V_1_2 2 // V1.2
#define BOARD_V_2_0 3 // V2.0
#define BOARD_WIFI_V_2_1 4 // WIFI V2.1
#define BOARD_UNIV_V_2_1 5 // UNIVERSIAL V2.1
// =====================================


// =====================================
//
// select board version
//
// =====================================

#define BOARD_VERSION BOARD_UNIV_V_2_1
#define SOFTWARE_VERSION 0x0100

#include "module_board.h"

// =====================================
//
// local definitions
//
// =====================================

// All local definitions are placed here
// ESP32 12-bit ADC
#if BOARD_VERSION == BOARD_WIFI_V_2_0 || BOARD_VERSION == BOARD_WIFI_V_2_1

    #define ANALOG_VAL_MAX 4095
    #define SPEED_MID_HIGH 2328
    #define SPEED_MID_LOW 908

    // analog switches
    #define MAINS_OFF 0
    #define MAINS_ON 1023
    #define MAINS_PUMP 4095

    #define DIR_REVERSE 0
    #define DIR_MID 1023
    #define DIR_FORWARD 4095

    #define LIGHT_OFF 0
    #define LIGHT_LOW 676
    #define LIGHT_LOW_TRAIN 1360
    #define LIGHT_HIGH_TRAIN 4095

    #ifdef ANALOG_LIGHT_1_SWITCH
        #define LIGHT_1_OFF 0
        #define LIGHT_1_LOW 676
        #define LIGHT_1_LOW_TRAIN 1360
        #define LIGHT_1_HIGH_TRAIN 4095
    #endif

// Atmega 328 10-bit ADC
#else

    #define ANALOG_VAL_MAX 1023
    #define SPEED_MID_HIGH 582
    #define SPEED_MID_LOW 227

    // analog switches
    #define MAINS_OFF 0
    #define MAINS_ON 1024
    #define MAINS_PUMP 2048

    #define DIR_REVERSE 0
    #define DIR_MID 1024
    #define DIR_FORWARD 2048

    #define LIGHT_OFF 0
    #define LIGHT_LOW 676
    #define LIGHT_LOW_TRAIN 1360
    #define LIGHT_HIGH_TRAIN 2048

    #ifdef ANALOG_LIGHT_1_SWITCH
        #define LIGHT_1_OFF 0
        #define LIGHT_1_LOW 676
        #define LIGHT_1_LOW_TRAIN 1360
        #define LIGHT_1_HIGH_TRAIN 2048
    #endif
#endif



// =====================================
//
// settings definitions
//
// =====================================

// max settings mytes
#define MODULE_MAX_SETTINGS 23

#define STATUS_OFF_FLASH 2000
#define STATUS_ERROR_FLASH 750
#define STATUS_ERROR_BLINK 1000
#define STATUS_READY_BLINK 500


#endif
