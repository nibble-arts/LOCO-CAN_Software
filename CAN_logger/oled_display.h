#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>


// Screen dimensions
#define DISPLAY_WIDTH	128
#define DISPLAY_HEIGHT	128 // Change this to 96 for 1.27" OLED.

// You can use any (4 or) 5 pins 
#define SCLK_PIN	2
#define MOSI_PIN	3
#define DC_PIN		4
#define CS_PIN		5
#define RST_PIN		6

// Color definitions
#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF

#define CHAR_WIDTH	6
#define CHAR_HEIGHT 8



class OLED_DISPLAY {

public:
	void begin(Adafruit_SSD1351* tft);
	void clear(void);
	void clear(uint8_t, uint8_t, uint8_t, uint8_t);
	void clearText(uint8_t, uint8_t, uint8_t, uint8_t);
	void clearLine(uint8_t);
	void drawText(char*, uint16_t);

	void drawByte(uint8_t, uint16_t);
	void drawHexByte(uint8_t, uint16_t);
	void drawInt(uint16_t, uint16_t);
	void drawHexInt(uint16_t, uint16_t);

	void textSize(uint8_t);
	void textColor(uint16_t);
	void cursor(uint8_t, uint8_t);
	void position(uint8_t, uint8_t);
	void hr(uint8_t, uint16_t);

private:
	Adafruit_SSD1351* _tft;
};



#endif