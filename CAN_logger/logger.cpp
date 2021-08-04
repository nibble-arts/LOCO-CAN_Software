#include <Arduino.h>
#include "logger.h"
#include "oled_display.h"


void LOG::begin(OLED_DISPLAY* display) {

	uint8_t i;

	_display = display;
	_dirty = true;
}

uint16_t LOG::add(DATA data) {

	uint8_t i;
	uint16_t idx = _find (data.id, data.uuid);

	if (idx < MAX_COUNT) {

		_data[idx].id = data.id;
		_data[idx].uuid = data.uuid;
		_data[idx].size = data.size;

		for (i = 0; i < 8; i++) {
			if (_data[idx].data[i] != data.data[i]) {
				_data[idx].data[i] = data.data[i];
				_dirty = true;
			}
			else {
			}
		}

		if (idx >= _count) {
			_count = idx + 1;
		}
	}
}

int16_t LOG::_find(uint16_t id, uint16_t uuid) {
	
	uint16_t i;
	
	// iterate existing entries
	for (i = 0; i < MAX_COUNT; i++) {
		
		// entry found > increment count
		if (_data[i].id == id && _data[i].uuid == uuid) {
			return i;
		}
	}
	
	return _count;
}

void LOG::render(void) {

	uint8_t idx, i = 0;
	uint8_t line;

	if (_dirty) {

		Serial.print(_count);
		Serial.println(" packets received");

		_display->clearText(0, 2, 21, 14);

		_display->clearText(13, 0, 3, 1);
		_display->cursor(13, 0);

		if (_count == 0) {
			_display->drawByte(_count, RED);
		}
		else {
			_display->drawByte(_count, GREEN);
		}

		// _display->drawText("packets", WHITE);


		while (i < _count) {

			Serial.print("  ");
			Serial.print(i);
			Serial.print(": ID: 0x");
			Serial.print(_data[i].id, HEX);
			Serial.print(" - UUID: 0x");
			Serial.print(_data[i].uuid, HEX);

			line = 2 + (i * 2);

			_display->cursor(0, line);
			_display->drawByte(i, CYAN);

			_display->cursor(2, line);
			_display->drawText("ID", WHITE);

			_display->cursor(5, line);
			_display->drawHexInt(_data[i].id, BLUE);

			_display->cursor(11, line);
			_display->drawText("UUID", WHITE);

			_display->cursor(16, line);
			_display->drawHexInt(_data[i].uuid, BLUE);


			for (idx = 0; idx < _data[i].size; idx++) {

				Serial.print(" ");
				Serial.print(_data[i].data[idx] & 0xFF, HEX);

				_display->position(16 + (idx * 14), ((line + 1) * CHAR_HEIGHT));
				_display->drawHexByte(_data[i].data[idx], MAGENTA);
			}

			Serial.println("");

			i++;
		}

		if (_count > 0) {
			Serial.println("");
		}
	}

	reset();
}

void LOG::reset(void) {
	uint16_t i;
	
	_count = 0;
	
	for (i = 0; i < MAX_COUNT; i++) {
		_data[i].count = 0;
	}
}