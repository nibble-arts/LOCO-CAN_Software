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

#include "settings.h"


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

#define BOARD_VERSION BOARD_V_2_0
#define SOFTWARE_VERSION 0x0100

#include "module_board.h"

// =====================================
//
// local definitions
//
// =====================================

// All local definitions are placed here
// value send interval ms
#define LIGHT_CURRENT_TIME 100


// =====================================
//
// settings definitions
//
// =====================================

// max settings bytes
#define MODULE_MAX_SETTINGS 14


struct SETUP_DATA {
    // use direction signal to selećt forward or reverse
    SETTINGS_BOOL   dir;

    // forward mapping
    SETTINGS_8   main_forw;
    SETTINGS_8   train_forw;
    SETTINGS_8   cab_forw;
    SETTINGS_8   instr_forw;
    SETTINGS_8   back_forw;
    SETTINGS_8   high_forw;
    SETTINGS_8   low_forw;
    SETTINGS_8   posit_forw;

    // reverse mapping
    SETTINGS_8   main_rew;
    SETTINGS_8   train_rew;
    SETTINGS_8   cab_rew;
    SETTINGS_8   instr_rew;
    SETTINGS_8   back_rew;
    SETTINGS_8   high_rew;
    SETTINGS_8   low_rew;
    SETTINGS_8   posit_rew;
};

// SETUP_DATA abc;

// einstellungen.type.name = "Modultype";

#endif
