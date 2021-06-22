/*
 * Loco Wifi Control
 * 
 * http request library
 * 
 * @autor: Thomas Winkler
 * @copyright: 2019-11-17
 * @lizence: CC0
 */

#include "SPIFFS.h"

#include "html.h"
#include "fileinfo.h"

FileInfo fileinfo;


void HTML::begin (void) {

  if (!SPIFFS.begin(true)) {
    Serial.println("Error mounting SPIFFS");
  }

  else {
    Serial.println("SPIFFS mounted");
  }

}


String HTML::show (HTTP http) {

  String page;
  String mime;






  /*
   * create path from http path
   * if no path, load default page
   */
  page = http.path();
  
  if (page == "") {
    page = HTML_DEFAULT_PAGE;
  }

  page = "/" + page;
  mime = fileinfo.mime(page);

  // default return string is 404
  String html = String ("404 - page not found");

  // load page file
  File file = SPIFFS.open(page);

  if (file) {

    if (file.available()) {

      if (mime == "text") {
        html = file.readString();
      }

      if (mime == "img") {
        html = file.read();
      }

      file.close();      
    }
    else {
      Serial.println("File not found");
    }
  }
  else {
    Serial.println("mount error");
  }

  return html;
}


/*
 * return header string by type
 * status = 200 > OK
 * status = 400 > bad request
 * anything else > 500 server error
 */
String HTML::header(int status) {

  String string;

  string = "HTTP/1.1 ";

  // add return status
  switch (status) {

    case 200:
      string += String(status) + " OK";
      break;

    case 400 :
      string += String(status) + " Bad Request";
      break;

    case 401 :
      string += String(status) + " Unauthorized";
      break;

    default:
      string += "500 Internal Server Error";
      break;
  }

  string += "Content-type: text/html";
  string += "Connection: close";

  return string;
}

