#include <Arduino.h>
#include "oled_display.h"



void OLED_DISPLAY::begin(Adafruit_SSD1351* tft) {
	_tft = tft;
	_tft->begin();
}

void OLED_DISPLAY::clear(void) {
	_tft->fillScreen(BLACK);
}

void OLED_DISPLAY::clear(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
	_tft->fillRect(x, y, w, h, BLACK);
}

void OLED_DISPLAY::clearText(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
	clear(x * CHAR_WIDTH, y * CHAR_HEIGHT, w * CHAR_WIDTH, h * CHAR_HEIGHT);
}

void OLED_DISPLAY::clearLine(uint8_t y) {
	clear(0, y * CHAR_HEIGHT, DISPLAY_WIDTH, CHAR_HEIGHT);
}

void OLED_DISPLAY::drawChar(uint8_t c, uint16_t color) {
	textColor(color);
	_tft->write(c);
}

void OLED_DISPLAY::drawText(char *text, uint16_t color) {
	textColor(color);
	_tft->print(text);
}

void OLED_DISPLAY::drawByte(uint8_t val, uint16_t color) {
	textColor(color);
	_tft->print(val);
}

void OLED_DISPLAY::drawHexByte(uint8_t val, uint16_t color) {
	textColor(color);
	_tft->print(val, HEX);
}

void OLED_DISPLAY::drawInt(uint16_t val, uint16_t color) {
	textColor(color);
	_tft->print(val);
}

void OLED_DISPLAY::drawHexInt(uint16_t val, uint16_t color) {
	textColor(color);
	_tft->print(val, HEX);
}

void OLED_DISPLAY::textSize(uint8_t size) {
	_tft->setTextSize(size);
}

void OLED_DISPLAY::textColor(uint16_t color) {
	_tft->setTextColor(color);
}

void OLED_DISPLAY::position(uint8_t x, uint8_t y) {
	_tft->setCursor(x, y);
}

void OLED_DISPLAY::cursor(uint8_t x, uint8_t y) {
	position(x * CHAR_WIDTH, y * CHAR_HEIGHT);
}

void OLED_DISPLAY::line(uint8_t x, uint8_t y, uint8_t w, uint16_t color) {
	_tft->drawFastHLine(x, y, w, color);
}

void OLED_DISPLAY::vline(uint8_t x, uint8_t y, uint8_t h, uint16_t color) {
	_tft->drawFastVLine(x, y, h, color);
}

void OLED_DISPLAY::block(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color) {
	_tft->fillRect(x, y, w, h, color);
}

void OLED_DISPLAY::hr(uint8_t y, uint16_t color) {
	line(0, y, _tft->width()-1, color);
}