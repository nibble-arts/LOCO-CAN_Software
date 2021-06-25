#ifndef EEPROM_SETUP_H
#define EEPROM_SETUP_H


#include <EEPROM.h>
#include "config.h"


class EEPROM_SETUP {

	public:
		EEPROM_SETUP(void);
		void begin(uint8_t, uint16_t, String);

		String name(void);
		void setName(String);

		uint8_t getByte(uint8_t);
		uint16_t getInt(uint8_t);
		uint32_t getLong(uint8_t);

		void setByte(uint8_t, uint8_t);
		void setInt(uint8_t, uint16_t);
		void setLong(uint8_t, uint32_t);

	private:
		uint8_t _max_settings;
		uint8_t _uuid;
		String _name;
};

#endif