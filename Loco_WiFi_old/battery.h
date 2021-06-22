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

#ifndef BATTERY_H
#define BATTERY_H


class BATTERY {

  public:
    void begin (void);
    float voltage (void);
    bool alive (void);

  private:
    bool _active = false;
};

#endif
