/*
 * Loco Wifi Control
 * 
 * loco controller class
 * 
 * @autor: Thomas Winkler
 * @copyright: 2019-11-17
 * @lizence: CC0
 */


#include "control.h"
#include "loco.h"


CONTROL::CONTROL (void) {
  _loco_count = 0;
//  reset();
}


/*
 * reset controler
 */
//void CONTROL::reset (void) {
//}


/*
 * add loco
 * return loco id
 * if no slot > return -1
 */
int CONTROL::add_loco (int uuid) {

  // has empty slot for new loco
  if (_loco_count < MAX_LOCOS) {

    // init loco with uuid
    _locos[_loco_count].init(uuid);

    _loco_count++;
    return _loco_count - 1;
  }

  return -1;
}


/*
 * get count of paired locos
 */
int CONTROL::count (void) {
  return _loco_count;
}


/*
 * get loco by id
 */
LOCO CONTROL::get_loco (int id) {

  if (id < _loco_count) {
    return _locos[id];
  }
}


/*
 * get loco id by uuid
 * returns the id
 * -1 if not
 */
int CONTROL::loco_exists (int uuid) {

  for (int i = 0; i < _loco_count; i++) {

    if (_locos[i].uuid() == uuid) {
      return i;
    }
  }

  return -1;
}

