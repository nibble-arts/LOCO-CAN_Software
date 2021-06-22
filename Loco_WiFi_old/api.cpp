/*
 * Loco Wifi Control
 * 
 * http api request library
 * 
 * @autor: Thomas Winkler
 * @copyright: 2019-11-17
 * @lizence: CC0
 */

#include "api.h"
#include "loco.h"
#include "control.h"


extern LOCO loco;
extern CONTROL control;


String API::call (HTTP http) {

Serial.println(http.param("uuid"));

  LOCO l;
  
  int idx = control.loco_exists(http.param("uuid").toInt());

  //===================
  // loco is paired
  if (idx != -1) {
    l = control.get_loco(idx);

Serial.print("loco: ");
Serial.println(http.param("uuid"));
Serial.println(l.get_name());

    l.exec();
    return l.serialize();
  }
  //===================

/*
  loco.target_data.uuid = http.param("uuid").toInt();

  loco.target_data.speed = http.param("speed").toInt();
  loco.target_data.dir = http.param("dir").toInt();

  loco.exec();
  
  return render();*/

  return "error=loco not paired";
}


String API::render(void) {
  return loco.serialize();
}

