/*
 * LOCO-CAN voltage class header file
 * 
 * @author: Thomas H Winkler
 * @copyright: 2020
 * @lizence: GG0
 */

#ifndef CURRENT_H
#define CURRENT_H

#include <Arduino.h>


class CURRENT {

  public:
    CURRENT(void);
    void begin(uint8_t port);
    long get(void);

  private:
    int _port;
    
};

#endif