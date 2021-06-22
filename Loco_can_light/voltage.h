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
    VOLTAGE(void);

    void begin(uint16_t, uint8_t); // max_val, absolute voltage to gnd
    void begin(uint16_t, uint8_t, uint8_t); // max_val, relative voltage between two ports

    int16_t get(void); // get voltage value
    void calibrate(float);

  private:
    uint16_t _max_val; // maximal dav value
    float _cal; // calibration value

    uint8_t _port_1;
    int8_t _port_2;
};

#endif