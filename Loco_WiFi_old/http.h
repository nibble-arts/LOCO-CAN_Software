/*
 * Loco Wifi Control
 * 
 * http request library
 * 
 * @autor: Thomas Winkler
 * @copyright: 2019-11-17
 * @lizence: CC0
 */

#ifndef HTTP_h
#define HTTP_h

#include <Arduino.h>
#include "config.h"

struct Param {
  String name;
  String value;
};

class HTTP {

  public:
    HTTP(void);
    void reset (void);
    void parse (String string);
    void set (String name, String value);
    void remove (String name);
    String param (String name);
    String header (String name);
    String path (void);
    String serialize (void);

  private:
    Param params[MAX_PARAM_COUNT];
    Param headers[MAX_HEADER_COUNT];
    int header_count;
    int param_count;
    String _path;

    int _param_exists (String name);
    int _parse_params (String params);
    Param _split_param (String key_value);

    int _add_header(Param parm);
    int _add_param(Param parm);
};

#endif
