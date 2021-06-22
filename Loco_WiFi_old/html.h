/*
 * Loco Wifi Control
 * 
 * html control code library
 * 
 * @autor: Thomas Winkler
 * @copyright: 2019-11-17
 * @lizence: CC0
 */

#ifndef HTML_h
#define HTML_h

#include <Arduino.h>
#include "http.h"


class HTML {

  public:
    void begin (void);
    String control (HTTP http);
    String show (HTTP http);
    
  private:
    String header (int status);

};


#endif
