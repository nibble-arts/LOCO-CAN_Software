/*
 * Loco Wifi Control
 * 
 * http request library
 * 
 * @autor: Thomas Winkler
 * @copyright: 2019-11-17
 * @lizence: CC0
 */

#include "http.h"

/*
 * parse http string
 */
HTTP::HTTP (void) {
  reset();
}


void HTTP::reset(void) {
  header_count = 0;
  param_count = 0;
}


/*
 * parse header string
 * extract GET, POST and HEADER
 */
void HTTP::parse (String string) {

  int pos;
  int end;
  Param header;
  String params;


  // ===========================
  // GET string
  pos = string.indexOf("GET /");

  // GET sequence found
  if (pos != -1) {

    // extract path
    end = string.indexOf("?");

    // has parameters
    if (end != -1) {

      _path = string.substring(pos + 5, end);
      params = string.substring(end);

      params.trim();
  
      // end at whitespace
      end = params.indexOf(" ");
      params = params.substring(1, end);
  
      _parse_params(params);
    }

    // only path
    else {

      _path = string.substring(5);

      end = _path.indexOf(" ");

      if (end != -1) {
        _path = _path.substring(0, end);
      }
      else {
        _path = string;
      }
    }
  }


  // extract header
  pos = (string.indexOf(":"));

  if (pos != -1) {
    
    header.name = string.substring(0,pos);
    header.value = string.substring(pos+1);
  
    header.name.trim();
    header.value.trim();
  
    _add_header(header);
  }
}


/*
 * set parameter
 */

void HTTP::set (String name, String value) {

  int i;
  Param param;

  // update parameter
  if ((i = _param_exists(name)) != -1) {
    params[i].value = value;
  }

  // insert new parameter
  else {

    param.name = name;
    param.value = value;

    _add_param(param);
  }
}


/*
 * delete parameter by name
 */
void HTTP::remove(String name) {

  if (int i = _param_exists(name)) {
    //TODO remove array entry
  }
}


/*
 * param exists
 * if exist > return index
 * else return -1
 */
int HTTP::_param_exists(String name) {

  for (int i=0; i < param_count; i++) {

    if (params[i].name == name) {
      return i;
    }
  }

  return -1;
}


/*
 * get http path
 */
String HTTP::path(void) {
  return _path;
}


/*
 * get parameter
 */
String HTTP::param(String name) {

  int i;
  
  if ((i = _param_exists(name)) != -1) {
    return params[i].value;
  }

  return "";
}


/*
 * get header parameter
 */
String HTTP::header(String name) {

  if (header_count > 1) {
    for (int i = 0;i < header_count;i++) {
  
      if (headers[i].name == name) {
        return headers[i].value;
      }
    }
  }

  return "";
}


/*
 * parameter
 * if max count reached, return false
 * else return count
 */
int HTTP::_add_header(Param head) {
  
  if (header_count < MAX_PARAM_COUNT) {
    headers[header_count] = head;

    header_count ++;
    return header_count;
  }

  else {
    return false;
  }
}


/*
 * split parameter string of key=value pairs separated by ampersant
 */
int HTTP::_parse_params(String string) {

  int pos;

  // iterate parameters
  while ((pos = string.indexOf("&")) != -1) {

    _add_param(_split_param(string.substring(0,pos)));

      // remove parameter from input string
      string = string.substring(pos+1);
  }

  // add rest of the parameter string
  _add_param(_split_param(string));

}


/*
 * split key=value pair into param struct
 */
Param HTTP::_split_param(String key_value) {

  int pos;
  Param param;
  
  pos = key_value.indexOf("=");

  // is key value pair
  if (pos != -1) {
    param.name = key_value.substring(0,pos);
    param.value = key_value.substring(pos+1);

    return param;
  }
}


/*
 * parameter
 * if max count reached, return false
 * else return count
 */
int HTTP::_add_param(Param param) {

  if (param_count < MAX_PARAM_COUNT) {
    params[param_count] = param;

    param_count ++;
    return param_count;
  }

  else {
    return false;
  }
}


/*
 * serialize parameters
 */
 
String HTTP::serialize() {

  String string("");
  string += "/";
  string += _path;
  string += "?";
  
  for (int i = 0; i < param_count; i++) {
    string += params[i].name + "=" + params[i].value;
    
    if (i < (param_count-1)) {
      string += "&";
    }
  }

  return string;
}

