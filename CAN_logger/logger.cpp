#include <Arduino.h>
#include "logger.h"
#include "oled_display.h"


void LOG::begin(OLED_DISPLAY* display) {

	uint8_t i;

	_display = display;
	_offset = 0;
	_last_percent = 0;

	reset();
}


// set timeout
void LOG::set_timeout(uint16_t time) {
	_time = time;
}


// add a data package to the list
uint16_t LOG::add(DATA data) {

	uint8_t i;
	int16_t idx = _find (data.id, data.uuid);


	// is valid id
	if (idx >= 0 and idx < MAX_COUNT) {

		_data[idx].id = data.id;
		_data[idx].uuid = data.uuid;
		_data[idx].size = data.size;


		if (_data[idx].count < 0xFF) {
			_data[idx].count++;
		}

		// presume old data

		// check for changed data
		for (i = 0; i < _data[idx].size; i++) {
			if (_data[idx].data[i] != data.data[i]) {
				_data[idx].data[i] = data.data[i];
			}
		}

		_count = _get_count();
	}
}


// find a id/uuid entry
// return the id of the entry or a free one
int16_t LOG::_find(uint16_t id, uint16_t uuid) {
	
	int16_t i;
	int16_t free = -1;

	// iterate existing entries
	for (i = 0; i < MAX_COUNT; i++) {
		
		// entry found > increment count
		if (_data[i].id == id && _data[i].uuid == uuid) {
			return i;
		}

		// first free entry
		if (_data[i].count == 0 && free == -1) {
			free = i;
		}
	}
	
	return free;
}


// remove empty entries and compress the rest
uint8_t LOG::_get_count(void) {

	uint8_t i;

	// iterate all entries
	for (i = 0; i < MAX_COUNT; i++) {

		// remove emty entries
		if (_data[i].count == 0) {
			return i;
		}
	}

	return MAX_COUNT;
}


void LOG::line_down(uint8_t cnt) {

	if ((_offset + cnt) < _count) {
		_offset += cnt;
	}

	// offset to last
	else {
		_offset = MAX_LINES;
	}
}

void LOG::line_up(uint8_t cnt) {

	if (_offset > (_count + cnt)) {
		_offset -= cnt;
	}

	// offset to first
	else {
		_offset = 0;
	}
}

// set display offset
void LOG::page_down(void) {

	line_down(MAX_LINES);
}

void LOG::page_up(void) {

	line_up(MAX_LINES);
}

// update paging
void LOG::_paging(void) {

	// limit offset to max
	if ((_offset + MAX_LINES) > _count) {
		_offset = _count - MAX_LINES;
	}

	// show scroll down
	if (_count > MAX_LINES) {

		if (_offset > 0) {
			_display->cursor(4, 15);
			_display->drawChar(ARROW_UP, RED);			
		}
		else {
			_display->cursor(4, 15);
			_display->drawChar(NO_ARROW, RED);
		}


		if ((_offset + MAX_LINES) < _count) {		
			_display->cursor(17, 15);
			_display->drawChar(ARROW_DOWN, RED);
		}
		else {
			_display->cursor(17, 15);
			_display->drawChar(NO_ARROW, RED);
		}
	}

	else {
		_offset = 0;
		_display->clearLine(15);
	}
}


// render result to serial and display
void LOG::render(void) {

	uint8_t idx, i = 0;
	uint8_t line;
	uint8_t max_line = 0;
	uint8_t rec_cnt;


	_paging();


	// update count
	_display->clearText(13, 0, 3, 1);
	_display->cursor(13, 0);

	if (_count == 0) {
		_display->drawByte(_count, RED);
	}
	else {
		_display->drawByte(_count, GREEN);
	}


	rec_cnt = 0;

	#ifdef SERIAL_OUT

		Serial.print(_count);
		Serial.println(" packets received");

	#endif

	// iterate entries
	for (i = 0; i < MAX_COUNT; i++) {


		#ifdef SERIAL_OUT

			if (_data[i].count != 0) {

				// serial out
				Serial.print("  ");
				Serial.print("ID: 0x");
				Serial.print(_data[i].id, HEX);
				Serial.print(" - UUID: 0x");
				Serial.print(_data[i].uuid, HEX);
				Serial.print(" - cnt: ");
				Serial.print(_data[i].count * 1000 / _time);

				Serial.print(" - data:");

				// display data packages
				for (idx = 0; idx < _data[i].size; idx++) {
					Serial.print(" ");
					Serial.print(_data[i].data[idx] & 0xFF, HEX);
				}

				Serial.println("");
			}

		#endif


		// DISPLAY OUTPUT
		// valid entry
		line = 2 + ((rec_cnt - _offset) * 2);


		if (_data[i].count != 0 && rec_cnt >= _offset && rec_cnt < (_offset + MAX_LINES)) {

			// show data
			// clear line and redraw
			_display->clearLine(line);

			// package id
			_display->cursor(0, line);
			_display->drawText("ID", WHITE);

			_display->cursor(3, line);
			_display->drawHexInt(_data[i].id, BLUE);

			// unique id
			_display->cursor(7, line);
			_display->drawText("UUID", WHITE);

			_display->cursor(12, line);
			_display->drawHexInt(_data[i].uuid, BLUE);

			// packages per second
			_display->cursor(17, line);
			_display->drawText("#", WHITE);

			_display->cursor(18, line);
			_display->drawByte(_data[i].count * 1000 / _time, CYAN);

			_display->clearLine(line + 1);

			// display data packages
			for (idx = 0; idx < _data[i].size; idx++) {

				_display->position(16 + (idx * 14), ((line + 1) * CHAR_HEIGHT));
				_display->drawHexByte(_data[i].data[idx], MAGENTA);
			}

			rec_cnt++;
		}


	}


	// clear unused lines
	i = _count;

	while (i < (MAX_LINES * 2)) {
		line = 2 + (i * 2);

		_display->clearLine(line);
		_display->clearLine(line + 1);

		 i++;
	}

	reset();
}


void LOG::progress(uint8_t percent) {

	uint8_t w;

	if (percent > 100) {
		percent = 100;
	}

	w = percent * DISPLAY_WIDTH / 100;

	// clear line
	if (percent < _last_percent) {
		_display->line(0, 10, DISPLAY_WIDTH, BLACK);
	}

	else {
		_display->line(0, 10, w, BLUE);
	}

	_last_percent = percent;
}


void LOG::reset(void) {
	uint16_t i;
	
	_count = 0;
	
	for (i = 0; i < MAX_COUNT; i++) {

		// remove entry
		if (_data[i].count == 0) {
			_data[i].id = 0;
			_data[i].uuid = 0;			
		}

		_data[i].count = 0;
	}
}