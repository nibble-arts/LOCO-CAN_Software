/*
   Loco Wifi Control

   locomotive class

   @autor: Thomas Winkler
   @copyright: 2019-11-17
   @lizence: CC0
*/

#ifndef LOCO_H
#define LOCO_H

#include <Arduino.h>
#include "config.h"


struct LOCO_DATA {

  int uuid;
  int speed;
  int dir;

  int tacho;

  bool light_for_left;
  bool light_for_right;
  bool light_back_left;
  bool light_back_right;

  bool train_light;

  int voltage_0;
  int voltage_1;
  int current_0;
  int current_1;

  float battery;
};


class LOCO {

  public:
    LOCO ();
    void init (int uuid);
    int uuid (void);
    void set_name (String name);
    String get_name (void);
    void set (String name, String value);
    void activate (void);
    void deactivate (void);
    String serialize (void);
    void exec (void);

    LOCO_DATA target_data;

  private:
    int _uuid;
    String _name;
    bool _active;
    LOCO_DATA _current_data;

};


#endif
