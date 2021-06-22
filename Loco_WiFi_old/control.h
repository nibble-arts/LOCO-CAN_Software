/*
 * Loco Wifi Control
 * 
 * loco controller class
 * 
 * @autor: Thomas Winkler
 * @copyright: 2019-11-17
 * @lizence: CC0
 */

#ifndef CONTROL_H
#define CONTROL_H

#include "loco.h"


class CONTROL {

  public:
    CONTROL (void);
    int add_loco (int uuid);
    int loco_exists (int uuid);
    LOCO get_loco (int id);
    int count (void);
//    void reset (void):

  private:
    LOCO _locos[MAX_LOCOS];
    int _loco_count;
};


#endif
