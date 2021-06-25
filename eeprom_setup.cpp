#include "eeprom_setup.h"

EEPROM_SETUP::EEPROM_SETUP(void) {}


void EEPROM_SETUP::begin(uint8_t max_settings, uint8_t uuid, String name) {

	_max_settings = max_settings;
	_uuid = uuid;
	_name = name;
}


String EEPROM_SETUP::name(void) {

}


void EEPROM_SETUP::setName(String) {

}


uint8_t EEPROM_SETUP::getByte(uint8_t) {

}


uint16_t EEPROM_SETUP::getInt(uint8_t) {

}


uint32_t EEPROM_SETUP::getLong(uint8_t) {

}


void EEPROM_SETUP::setByte(uint8_t, uint8_t) {

}


void EEPROM_SETUP::setInt(uint8_t, uint16_t) {

}


void EEPROM_SETUP::setLong(uint8_t, uint32_t) {

}