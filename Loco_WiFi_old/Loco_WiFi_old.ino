/*
 * Loco-WIFI control
 * 
 * @author: Thomas Winkler
 * @copyright: 2019-11-17
 * @lizense: CC0
 * 
 * based on Rui Santos
 * Complete project details at https://randomnerdtutorials.com  
 */

// Load libraries
#include <WiFi.h>

#include "config.h"
#include "board.h"

#include "http.h"
#include "api.h"
#include "led.h"
#include "html.h"
#include "battery.h"

#include "control.h"

#include "can_com.h"


HTTP http;
HTML html;
API api;

CONTROL control;

LED internal_led (INTERNAL_LED);
LED led1 (LED1);
LED led2 (LED2);

BATTERY battery;

// network credentials from the config.h file
const char* ssid     = WIFI_SSID;
const char* password = WIFI_PASSWORD;

// Set web server port number to 80
WiFiServer server(WIFI_PORT);





void setup() {

  Serial.begin(115200);
Serial.println("Start");
  // html.begin();
  
  internal_led.on();
  // led1.on();
  // led2.on();

  // delay(1000);

  // led1.off();
  // led2.off();


  // // Connect to Wi-Fi network with SSID and password
  // Serial.print("Starting Access Point");
  // // Remove the password parameter, if you want the AP (Access Point) to be open
  // WiFi.softAP(ssid, password);

  // //IPAddress IP = WiFi.softAPIP();
  // IPAddress IP(192, 168, 4, 1);
  
  // Serial.print("AP IP address: ");
  // Serial.println(IP);
  
  // server.begin();

  // http.reset();
Serial.println("Init LED");

  internal_led.blink(500);

  // control.add_loco(12345);
  // control.add_loco(23456);

  // Serial.print("Paired locos: ");
  // Serial.println(control.count());

}



void loop(){
  
  // WiFiClient client = server.available();   // Listen for incoming clients

  // String line;

  // if (client) {                             // If a new client connects,
  //   Serial.println("New Client.");          // print a message out in the serial port

  //   String currentLine = "";                // make a String to hold incoming data from the client
  //   http.reset();

  //   while (client.connected()) {            // loop while the client's connected
    
  //     if (client.available()) {             // if there's bytes to read from the client,
      
  //       char c = client.read();             // read a byte, then
  //       //Serial.write(c);                    // print it out the serial monitor
  //       line += c;
        
  //       if (c == '\n') {                    // if the byte is a newline character

  //         // parse http string and get parameters

  //         http.parse(line);

  //         // if the current line is blank, you got two newline characters in a row.
  //         // that's the end of the client HTTP request, so send a response:
  //         if (currentLine.length() == 0) {


  //           // call api
  //           if (http.path() == "api") {
  //             client.print(api.call(http));
  //           }

  //           // call html control page
  //           else {
  //             client.print(html.show(http));
  //           }


  //           // Break out of the while loop
  //           break;
  //         }

  //         // if you got a newline, then clear currentLine
  //         else {
  //           currentLine = "";
  //         }

  //         // clear the line
  //         line = "";
  //       }

  //       // if you got anything else but a carriage return character,
  //       // add it to the end of the currentLine
  //       else if (c != '\r') {
  //         currentLine += c;
  //       }
  //     }
  //   }


  //   // Close the connection
  //   client.stop();
  //   Serial.println("Client disconnected.");
  //   Serial.println("");
  // }

Serial.println("blink");

  internal_led.update();

  // if (!battery.alive()) {
  //   Serial.println(battery.voltage()); 
  // }
}

