#ifndef LOGGER_H
#define LOGGER_H

#include "oled_display.h"

#define MAX_COUNT 32

struct DATA {
	uint16_t id;
	uint16_t uuid;
	uint8_t data[8];
	uint16_t count;
	uint8_t size;
};



class LOG {
	public:
		void begin(OLED_DISPLAY*);
		uint16_t add(DATA);
		void render(void);
		void reset(void);
	
	private:
		DATA _data[MAX_COUNT];
		uint16_t _count;
		int16_t _find(uint16_t id, uint16_t uuid);
		OLED_DISPLAY* _display;
		uint8_t _current_count;
		bool _dirty;
};


#endif