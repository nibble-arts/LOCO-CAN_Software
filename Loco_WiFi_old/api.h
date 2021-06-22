/*
 * Loco Wifi Control
 * 
 * http api request library
 * 
 * @autor: Thomas Winkler
 * @copyright: 2019-11-17
 * @lizence: CC0
 */

#ifndef API_h
#define API_h

#include <Arduino.h>
#include "config.h"
#include "http.h"


class API {

  public:
    String call (HTTP http);

  private:
    String render();
  
};


#endif
