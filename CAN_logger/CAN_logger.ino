#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>
#include <RotaryEncoder.h>

#include "can_com.h"
#include "simpletimeout.h"
#include "oled_display.h"
#include "logger.h"
#include "button.h"
#include "status.h"
#include "usb.h"
#include "loco.h"


// scan all x milliseconds
#define SCAN_TIME 5000

#define UP_PORT 7
#define DOWN_PORT 8
#define BUTTON_PORT 9

#define STATUS_LOCO 0
#define STATUS_LOGGER 1
#define STATUS_USB 2

#define DEBUG

// **************************************************

CAN_COM can;
CAN_MESSAGE message;

SIMPLETIMEOUT timeout;
LOG logger;
LOCO loco;

OLED_DISPLAY display;
Adafruit_SSD1351 tft(DISPLAY_WIDTH, DISPLAY_HEIGHT, CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);

RotaryEncoder encoder(UP_PORT, DOWN_PORT, RotaryEncoder::LatchMode::TWO03);
BUTTON b;

STATUS stat;
bool redraw;


// **************************************************
void setup(void) {

	Serial.begin(115200);
	
	can.begin(500E3);

	#ifdef DEBUG
		Serial.println();
		Serial.print("Device UUID: ");
		Serial.println(can.uuid(), HEX);
	#endif

	timeout.begin(SCAN_TIME);

	// start display
	display.begin(&tft);
	display.clear();

	logger.begin(&display);
	logger.set_timeout(SCAN_TIME);

	redraw = true;

	// set initial state
	stat.set(STATUS_LOCO);

	b.begin(BUTTON_PORT);
	stat.begin(2);

}


void loop(void) {

	DATA data;
	uint8_t i;
	uint16_t id;
	uint16_t count;
	static int pos = 0;


	// MESSAGE RECEIVED
	id = can.read(&message);
	

	// ROTARY ENCODER ACTIVITY
	encoder.tick();

	int newPos = encoder.getPosition();

	if (pos != newPos) {

		if ((int)encoder.getDirection() > 0) {
			logger.line_up(1);
		}
		else {
			logger.line_down(1);
		}

		encoder.setPosition(0);
	}


	// BUTTON ACTIVITY
	if (b.get()) {

		// status.next();
		stat.next();

		redraw = true;
	}


	// ========================================================
	// DRAW DISPLAY
	if (stat.is(STATUS_LOCO)) {

		if (redraw) {
			redraw = false;

			show_loco(&display);
		}

		loco.update(&message);
	}


	// DRAW LOGGER SCREEN
	if (stat.is(STATUS_LOGGER)) {

		// new message
		if (id) {
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

		if (redraw) {
			redraw = false;

			show_logger(&display);
		}

		// render messages
		if (timeout.update()) {
			logger.render();
		}

		else {
			logger.progress(timeout.progress());
		}
	}

	// DRAW SERIAL USB
	if (stat.is(STATUS_USB)) {

		// new message
		if (id) {
			USB::send(message);
		}

		if (redraw) {
			redraw = false;

			show_usb(&display);
		}

	}
}


void show_loco(OLED_DISPLAY* display) {

	// show display init message
	display->clear();

	display->textSize(1);
	display->cursor(0, 0);
	display->drawText("LOCO-CAN", WHITE);

	display->cursor(17, 0);
	display->drawText("V1.0", RED);

	logger.progress(100);

	loco.begin(display);

}


void show_logger(OLED_DISPLAY* display) {

	// show display init message
	display->clear();

	display->textSize(1);
	display->cursor(0, 0);
	display->drawText("BUS-MONITOR", WHITE);

	display->cursor(17, 0);
	display->drawText("V1.0", RED);

	logger.progress(100);

}


void show_usb(OLED_DISPLAY* display) {

	display->clear();

	display->textSize(1);
	display->cursor(0, 0);
	display->drawText("SERIAL OUT ON", WHITE);

	logger.progress(100);

	display->cursor(0, 3);
	display->drawText("Connect to USB", WHITE);
}