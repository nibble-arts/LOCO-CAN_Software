#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>

#include "can_com.h"
#include "simpletimeout.h"
#include "oled_display.h"
#include "logger.h"




// **************************************************

CAN_COM can;
CAN_MESSAGE message;

SIMPLETIMEOUT timeout;
LOG logger;

OLED_DISPLAY display;
Adafruit_SSD1351 tft(DISPLAY_WIDTH, DISPLAY_HEIGHT, CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);


// **************************************************
void setup(void) {

	Serial.begin(115200);
	
	can.begin(500E3);
	timeout.begin(5000);


	// start display
	display.begin(&tft);
	logger.begin(&display);


	// show display init message
	display.clear();

	display.textSize(1);
	display.cursor(0, 0);
	display.drawText("CAN-MONITOR", WHITE);

	display.cursor(17, 0);
	display.drawText("V1.0", RED);

	display.hr(10, BLUE);
}


void loop(void) {

	DATA data;
	uint8_t i;
	uint16_t id;
	uint16_t count;
	
	if (id = can.read(&message)) {

		data.id = id;
		data.uuid = message.uuid;
		data.size = message.size;

		for (i = 0; i < 8; i++) {

			if (i < message.size) {
				data.data[i] = message.data[i];
			}
			else {
				data.data[i] = 0;
			}
		}
		
		logger.add(data);
	}
	
	if (timeout.update()) {
		logger.render();
	}
}