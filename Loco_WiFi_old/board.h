/*
 * Loco Wifi Control
 * 
 * board pinning
 * 
 * @autor: Thomas Winkler
 * @copyright: 2019-11-17
 * @lizence: CC0
 */

#ifndef BOARD_h
#define BOARD_h


#if BOARD_VERSION == BOARD_DEVKIT_V1
  #include "board_devkit_v1.h"
#endif

#if BOARD_VERSION == BOARD_LOLIN_D32
  #include "board_lolin_d32.h"
#endif


#endif
