/*
 * Loco Wifi Control
 * 
 * battery control class
 * checks the supply voltage of the controller
 * 
 * @autor: Thomas Winkler
 * @copyright: 2019-11-17
 * @lizence: CC0
 */


#include <Arduino.h>
#include "battery.h"
#include "board.h"


float BATTERY::voltage (void) {

  if (BATTERY_PORT != -1) {
    return analogRead(BATTERY_PORT) / 4096.0 * 7.455;
  }

  return 0;
}


bool BATTERY::alive (void) {

  if (voltage() <= BATTERY_MIN_VOLT) {
    return false;
  }

  return true;
}

