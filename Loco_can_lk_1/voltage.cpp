/*
 * LOCO-CAN current class
 * 
 * @author: Thomas H Winkler
 * @copyright: 2020
 * @lizence: GG0
 */

#include "voltage.h"
#include <Arduino.h>

/*
 * init current port
 */
VOLTAGE::VOLTAGE(void) {
}


void VOLTAGE::begin(uint16_t max_val, uint8_t port) {
    begin(max_val, port, -1);
}


void VOLTAGE::begin(uint16_t max_val, uint8_t port_1, uint8_t port_2) {

    _max_val = max_val;
    _cal = 1;

    _port_1 = port_1;
    _port_2 = port_2;

    pinMode(port_1, INPUT_PULLUP);

    if (port_2 != -1) {
        pinMode(port_2, INPUT_PULLUP);
    }
}


/*
 * set calibration value
 */
void VOLTAGE::calibrate(float cal) {
    _cal = cal;
}


/*
 * get current value
 * output value in mV as integer
 */
int16_t VOLTAGE::get(void) {

    float v0 = 0;
    float v1;

    v0 = analogRead(_port_1);
    v1 = 0;
    
    // get relative value
    if (_port_2 = -1) {
        v1 = analogRead(_port_2);
    }

    return (int)((v1 - v0) * _cal);
}
