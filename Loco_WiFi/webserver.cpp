/*
 * LOCO-CAN Webserver

 * @author: Thomas H Winkler
 * @copyright: 2020
 * @lizence: GG0
 */


#include "config.h"
#include "can_protocol.h"

#include "webserver.h"


// init webserver on port
WEBSERVER::WEBSERVER(int port) {

	_server = new AsyncWebServer(port);
}


// connect to wifi
void WEBSERVER::wifi(char* ssid, char* password) {
    _connect(false, ssid, password);
}


// create access point
void WEBSERVER::ap(char* ssid, char* password) {
    _connect(true, ssid, password);
}


// connect to wifi / create access point
void WEBSERVER::_connect(bool ap, char* ssid, char* password) {

	disconnect();

	_ap = ap;
	_ssid = ssid;
	_password = password;
}


// disconnect wifi
void WEBSERVER::disconnect(void) {
	WiFi.disconnect();

    Serial.println("WiFi disconnected");
}


// begin webserver
void WEBSERVER::begin() {


    SPIFFS.begin();


	// create ACCESS POINT
    if (_ap == true) {

        Serial.println("Configuring access point");

        WiFi.softAP(_ssid, _password);

        // WiFi.begin();
  
        Serial.println("Server started");

        _ip = WiFi.softAPIP();

        Serial.print("Wifi access point IP ");
    }

    // use WIFI client mode
    else {

        Serial.print("Connect to WiFi ");
        Serial.println(_ssid);

        WiFi.begin(_ssid, _password);

        // wait for connection
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }

        _ip = WiFi.localIP();

        Serial.print("WiFi connected with IP ");
    }

    Serial.println(_ip);


    // =============================================
    // serve static pages
    _server->serveStatic("/", SPIFFS, "/").setDefaultFile("index.htm");


    // =============================================
    // administration page
    // _server->on("/admin", HTTP_GET, [this] (AsyncWebServerRequest *request) {
    //     request->send(200, "text/html", _ip.toString());
    // });


    // =============================================
    // GET API call
    _server->on("/api", HTTP_GET, [this] (AsyncWebServerRequest *request) {
      
        String cmd;
        StaticJsonDocument<256> json;
        String output;


        // int cnt = request->params();

        if (request->hasParam("cmd")) {

            cmd = request->getParam("cmd")->value();

            Serial.print("API access: ");
            Serial.println(cmd);

            // ADD STATUS
            json["status"]["ip"] = _ip.toString();

            if (_ap) {
                json["status"]["type"] = "Access Point Mode";
            }

            else {
                json["status"]["type"] = "WiFi Client";
            }


            // =======================================
            // LOAD DATA
            if (cmd == "load") {
                json["data"][0]["type"] = "DRIVE";
                json["data"][0]["uuid"] = "2237498787";
                json["data"][0]["data"] = "0100010010";

                json["data"][1]["type"] = "LIGHT";
                json["data"][1]["uuid"] = "098745828";
                json["data"][1]["data"] = "00010010";
            }



        }
        
        else {
            json["error"] = "no command";
        }

        serializeJson(json, output);

        // request->addHeader("Access-Control-Allow-Origin", "*");
        request->send(200, "application/json", output);
    });


    // =============================================
    // POST to API
    _server->on("/api", HTTP_POST, [this](AsyncWebServerRequest *request) {
      
        String message;

        Serial.println("POST received");

        int cnt = request->params();
        Serial.print("params ");
        Serial.println(cnt);

        if (request->hasParam("cmd", true)) {
            message = request->getParam("cmd", true)->value();
        }
        
        else {
            message = "No message sent";
        }
        
        request->send(200, "text/plain", "POST: " + message + " with " + String(cnt) + " params");
    });


    // =============================================
    // nothing found
    _server->onNotFound( [](AsyncWebServerRequest *request) {
   		request->send(404, "text/plain", "page Not found");
    });


    _server->begin();
}


