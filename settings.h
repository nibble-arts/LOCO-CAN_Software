/*
 * LOCO-CAN module settings file
 * 
 * @author: Thomas H Winkler
 * @copyright: 2020
 * @lizence: GG0
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>


#include "eeprom_setup.h"
#include "can_protocol.h"
#include "config.h"


// convert bytes to a 16/32 bit integer
#define char2int(MSB, LSB) (uint16_t)(((uint8_t) MSB & 0xFF) << 8 | ((int8_t) LSB & 0xFF))
#define char2long(MSB, LSB, MSB1, LSB1) (((uint32_t) ((uint8_t) MSB)) & 0xFF) << 24 | (((uint32_t) ((uint8_t) LSB)) & 0xFF) << 16 | (((uint32_t) ((uint8_t) MSB1)) & 0xFF) << 8 | (((int8_t) LSB1) & 0xFF)

#define MSB(BYTE) (uint8_t)(((uint8_t) BYTE >> 4) & 0x0F)
#define LSB(BYTE) (uint8_t)((uint8_t) BYTE & 0x0F)

// =====================================
//
// CLASS HEADER
//
// =====================================

class SETTINGS {

	public:
		void begin(uint8_t uuid, uint8_t version, uint8_t type, uint8_t max_settings);

		// communication methods
		void sendGlobalRequest(void); // send request to all modules
		void sendRequest(uint16_t uuid); // send request to UUID-module
		void sendRequest(uint16_t uuid, uint8_t index); // send value request to UUID-module
		void sendRequest(uint16_t uuid, uint8_t index, uint8_t cnt); // send multiple value request to UUID-module

		void setupName(uint16_t uuid, String name); // send setup name data

		void setupValue(uint16_t uuid, uint8_t* value, uint8_t index); // send one setup value
		void setupValue(uint16_t uuid, uint8_t* values, uint8_t index, uint8_t cnt); // send setup values

		void sendInfoReply(uint8_t type); // reply module info
		void sendNameReply(void); // reply module name

		void sendValueReply(uint8_t index); // reply one module value
		void sendValueReply(uint8_t index, uint8_t size); // reply module values

		bool readName(uint8_t* buffer, uint8_t size, uint8_t cnt);


		// storage methods
		String name(void);
		void setName(uint8_t*);

		uint8_t getByte(uint8_t);
		uint16_t getInt(uint8_t);
		uint32_t getLong(uint8_t);

		void setByte(uint8_t, uint8_t);
		void setInt(uint16_t, uint8_t);
		void setLong(uint32_t, uint8_t);

	private:

		EEPROM_SETUP _setup;
		
		uint8_t _data[EEPROM_MAX_DATA];
		uint8_t _i;
		uint8_t _buffer[8];
		uint16_t _version;
		uint8_t _type;
		uint8_t _max_settings;

		uint8_t _name[MODULE_NAME_LENGTH];

		void _sendVersion(uint8_t max_pack_cnt);
		void _sendName(uint16_t uuid, String name, uint8_t max_pack_cnt, uint16_t can_id);
		uint8_t _createCnt(uint8_t cnt, uint8_t max_cnt);
};


#endif