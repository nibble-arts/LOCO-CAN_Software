#ifndef LOGGER_H
#define LOGGER_H

#include "oled_display.h"

#define MAX_COUNT 16
#define MAX_LINES 6

// uncomment to send data to serial out
#define SERIAL_OUT true


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
		void set_timeout(uint16_t);
		uint16_t add(DATA);
		void render(void);
		void reset(void);

		void line_up(uint8_t);
		void line_down(uint8_t);
		void page_up(void);
		void page_down(void);

		void progress(uint8_t);

	
	private:
		DATA _data[MAX_COUNT];

		uint16_t _count;
		uint8_t _current_count;
		uint16_t _time;
		OLED_DISPLAY* _display;
		uint8_t _offset;
		uint8_t _last_percent;

		int16_t _find(uint16_t id, uint16_t uuid);
		uint8_t _get_count(void);

		void _paging(void);
};


#endif