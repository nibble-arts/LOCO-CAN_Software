//
// A simple server implementation showing how to:
//  * serve static messages
//  * read GET and POST parameters
//  * handle missing pages / 404s
//

#include <Arduino.h>

// #ifdef ESP32
//     #include <SPIFFS.h>
//     #include <WiFi.h>
//     #include <AsyncTCP.h>
// #elif defined(ESP8266)

// #include <ESP8266WiFi.h>
// #include <ESPAsyncTCP.h>
// #endif

// #include <ESPAsyncWebServer.h>

// #include <ArduinoJson.h>
#include "config.h"
#include "module_board.h"

#include "intelliled.h"
#include "can_protocol.h"
#include "loco_config.h"

#include "webserver.h"
#include "can_com.h"



struct DATA {
  double uuid;
  int type;
};


INTELLILED led(CAN_STATUS_LED);
WEBSERVER server(WIFI_PORT);


void setup() {

  // disable watchdogs
  disableCore0WDT();
  disableCore1WDT();
  disableLoopWDT();

  led.off();

  Serial.begin(115200);

  Serial.println("");

  // select WiFi connection type
  if (WIFI_AP_MODE == true) {
    server.ap((char*)AP_SSID, (char*)AP_PASSWORD);
  }
  else {
    server.wifi((char*)WIFI_SSID, (char*)WIFI_PASSWORD);
  }

  server.begin();

  led.blink(BLINKTIME);

  DATA data[16];

  data[0].uuid = 1234567;
  data[0].type = 0x47;

  data[1].uuid = 9876543;
  data[1].type = 0xF1;
}


void loop() {

  // blink heartbeat
  led.update();

}
