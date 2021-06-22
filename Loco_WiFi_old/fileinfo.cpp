/*
 * Loco Wifi Control
 * 
 * file name class
 * 
 * @autor: Thomas Winkler
 * @copyright: 2019-11-17
 * @lizence: CC0
 */


#include <Arduino.h>
#include "fileinfo.h"


String FileInfo::path (String string) {
  return split(string).path;
}


String FileInfo::filename (String string) {
  return split(string).filename;
}


String FileInfo::extension (String string) {
  return split(string).extension;
}


String FileInfo::mime (String string) {

  int i;
  String mime = String ("unkonwn");
  String ext = split(string).extension;
  
  String text[3] = {"html","txt","js"};
  String img[5] = {"jpg","jpeg","png","gif","ico"};

  for (i = 0; i < sizeof(text); i++) {
    if (ext == text[i]) {
      mime = "text";
    }
  }

  for (i = 0; i < sizeof(img); i++) {
    if (ext == img[i]) {
      mime = "img";
    }
  }

  return mime;
}


FILEINFO FileInfo::split(String string) {

  int pos = string.lastIndexOf(".");

  // extension point found
  if (pos != -1) {
    _info.extension = string.substring(pos + 1);
    string = string.substring(0, pos);
  }

  // split filename
  pos = string.lastIndexOf("/");

  // slash found
  if (pos != -1) {
    _info.path = string.substring(0, pos);
    _info.filename = string.substring(pos + 1);
  }

  else {
    _info.path = "";
    _info.filename = string;
  }

  return  _info;
}

