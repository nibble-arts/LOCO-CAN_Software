/*
 * Loco Wifi Control
 * 
 * locomotive class
 * 
 * @autor: Thomas Winkler
 * @copyright: 2019-11-17
 * @lizence: CC0
 */

#include <Arduino.h>
#include "loco.h"
#include "battery.h"


LOCO loco;
extern BATTERY battery;


LOCO::LOCO (void) {
  set_name ("");
  deactivate();
}


void LOCO::init (int uuid) {
  _uuid = uuid;
}


/*
 * get uuid of loco
 */
int LOCO::uuid (void) {
  return _uuid;
}


/*
 * set/get loco name
 */
void LOCO::set_name (String name) {
  _name = name;
}


String LOCO::get_name (void) {
  return _name;
}


/*
 * activate/deactivate loco
 */
void LOCO::activate () {
  _active = true;
}

void LOCO::deactivate() {
  _active = false;
}


/*
 * execute functions
 * create current data
 */
void LOCO::exec () {


//TODO calculate current data from loco status

  
  
  _current_data = target_data;
  _current_data.battery = battery.voltage();

}


String LOCO::serialize(void) {

  String string;

  string += "battery=" + String(_current_data.battery) + "&";

  string += "uuid=" + String(_current_data.uuid) + "&";

  string += "speed=" + String(_current_data.speed) + "&";
  string += "dir=" + String(_current_data.dir) + "&";

  string += "tach=" + String(_current_data.tacho) + "&";

  string += "l_fl=" + String(_current_data.light_for_left) + "&";
  string += "l_fr=" + String(_current_data.light_for_right) + "&";
  string += "l_bl=" + String(_current_data.light_back_left) + "&";
  string += "l_br=" + String(_current_data.light_back_right) + "&";

  string += "l_t=" + String(_current_data.train_light) + "&";

  string += "v0=" + String(_current_data.voltage_0) + "&";
  string += "v1=" + String(_current_data.voltage_1) + "&";
  string += "c0=" + String(_current_data.current_0) + "&";
  string += "c1=" + String(_current_data.current_1);

  return string;
}

