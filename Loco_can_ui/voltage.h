/*
 * LOCO-CAN voltage class header file
 * 
 * @author: Thomas H Winkler
 * @copyright: 2020
 * @lizence: GG0
 */

#ifndef VOLTAGE_H
#define VOLTAGE_H

#include <Arduino.h>


class VOLTAGE {

  public:
    VOLTAGE(uint16_t); // create voltage class, set maximal value
    VOLTAGE(uint16_t, uint16_t); // create voltage class, set maximal value and calibration

    void begin(uint8_t port); // absolute voltage to gnd
    void begin(uint8_t, uint8_t); // relative voltage between two ports
    long get(void);

  private:
    uint16_t _max_val; // maximal dav value
    uint16_t _cal; // calibration value

    uint8_t _port_1;
    int8_t _port_2;
};

#endif