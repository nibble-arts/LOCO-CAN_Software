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
VOLTAGE::VOLTAGE(uint16_t max_val) {
    _max_val = max_val;
}


VOLTAGE::VOLTAGE(uint16_t max_val, uint16_t cal) {

    _max_val = max_val;
    calibrate(cal);
}

void VOLTAGE::begin(uint8_t port) {
    begin(port, -1);
}


void VOLTAGE::begin(uint8_t port_1, uint8_t port_2) {

    _cal = 1;

	_port_1 = port_1;
    _port_2 = port_2;

	pinMode(port_1, INPUT);

    if (port_2 != -1) {
        pinMode(port_2, INPUT);
    }
}


/*
 * set calibration
 */
void VOLTAGE::calibrate(float cal) {
    _cal = cal;
}


/*
 * get current value
 */
float VOLTAGE::get(void) {

    float v0 = 0;
    float v1;

    v0 = 0;
    v1 = analogRead(_port_1);
    
    // get relative value
    if (_port_2 = -1) {
        v1 = analogRead(_port_2);
    }

    return (v1 - v0) * _cal;
}
