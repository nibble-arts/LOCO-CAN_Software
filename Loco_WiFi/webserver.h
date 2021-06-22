/*
 * LOCO-CAN Controller WebServer header file
 * 
 * @author: Thomas H Winkler
 * @copyright: 2020
 * @lizence: GG0
 */


#ifndef _WEBSERVER_H_
#define _WEBSERVER_H_


#ifdef ESP32
    #include <SPIFFS.h>
    #include <WiFi.h>
    #include <AsyncTCP.h>
#elif defined(ESP8266)

	#include <ESP8266WiFi.h>
	#include <ESPAsyncTCP.h>
#endif

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>



class WEBSERVER {

	public:
		WEBSERVER(int port); // create webserver
		void wifi(char* ssid, char* password); // connect to wifi
		void ap(char* ssid, char* password); // create access point
		void disconnect(void); // end wifi connection

		void begin(void); // start server

	private:
		bool _ap;
		IPAddress _ip;
		char* _ssid;
		char* _password;

		void _connect(bool, char*, char*);
		void _notFound(void);
		AsyncWebServer* _server;

};

#endif /* _WEBSERVER_H_ */