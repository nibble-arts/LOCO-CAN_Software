/*
 * LOCO-CAN module settings file
 * 
 * @author: Thomas H Winkler
 * @copyright: 2020
 * @lizence: GG0
 */

#include "settings.h"
#include "can_com.h"
#include "can_protocol.h"


extern CAN_COM can_com;

// start setting
// init uuid and default name, if not valid in EEPROM
void SETTINGS::begin(uint8_t uuid, uint8_t version, uint8_t type, uint8_t max_settings) {
	_version = version;
	_type = type;
	_max_settings = max_settings;

	_setup.begin(max_settings, uuid, "Light");
}


// ================================================
//
// REQUESTS

// global request
void SETTINGS::sendGlobalRequest(void) {

	_buffer[0] = 0xFF;

	can_com.send(_buffer, 1, CAN_ID_REQUEST);

}

// UUID info request
void SETTINGS::sendRequest(uint16_t uuid) {

	_buffer[0] = MSB(uuid);
	_buffer[1] = LSB(uuid);

	can_com.send(_buffer, 2, CAN_ID_REQUEST);

}

// value request
void SETTINGS::sendRequest(uint16_t uuid, uint8_t index) {

	_buffer[0] = MSB(uuid);
	_buffer[1] = LSB(uuid);

	_buffer[2] = index;

	can_com.send(_buffer, 3, CAN_ID_REQUEST);

}

// multiple value request
// index = start index
// cnt = count of following bytes
void SETTINGS::sendRequest(uint16_t uuid, uint8_t index, uint8_t cnt) {

	_buffer[0] = MSB(uuid);
	_buffer[1] = LSB(uuid);

	_buffer[2] = index;
	_buffer[3] = cnt;

	can_com.send(_buffer, 4, CAN_ID_REQUEST);

}


// ================================================
//
// REPLYS

// send info reply
void SETTINGS::sendInfoReply(uint8_t type) {

	// get packet count (verson + name)
	uint8_t packets = ceil((float)_setup.name().length() / 6) + 1;

	// send version and type
	// and name
	_sendVersion(packets);
	_sendName(0, _setup.name(), packets, CAN_ID_REPLY);

}



void sendNameReply(void) {

}


// send value reply with one byte
// buffer: buffer of values
void SETTINGS::sendValueReply(uint8_t index) {
	sendValueReply(index, 1);
}


void SETTINGS::sendValueReply(uint8_t index, uint8_t cnt) {

	_i = 0;

	if (cnt > 8) {
		cnt = 8;
	}

	while ((index + _i) < _max_settings && _i < cnt) {
		_buffer[_i] = _setup.getByte(index + _i);
		_i++;
	}

	can_com.send(_buffer, _i, (CAN_ID_REPLY | (index + 1)) & 0x7F);

}


// ================================================
//
// SET REQUESTS

// send one value
void SETTINGS::setupValue(uint16_t uuid, uint8_t* value, uint8_t index) {
	setupValue(uuid, value, index, 1);
}


void SETTINGS::setupValue(uint16_t uuid, uint8_t* buffer, uint8_t index, uint8_t size) {

	if (index < 0xFF) {

		// add UUID to buffer
		_buffer[0] = MSB(uuid);
		_buffer[1] = LSB(uuid);


		// add data to buffer
		_i = 0;

		while (_i < size && _i < CAN_VALUE_MAX_SIZE && (index + _i) < _max_settings) {
			_buffer[_i + 2] = _setup.getByte(index + _i);
			_i++;
		}

		// send
		can_com.send(_buffer, _i + 2, CAN_ID_REPLY | (index + 1));
	}
}


// send name
void SETTINGS::setupName(uint16_t uuid, String name) {

	uint8_t max_packets = (ceil)((float)name.length() / CAN_NAME_MAX_SIZE);

	_sendName(uuid, name, max_packets, CAN_ID_SETUP);
}




// ================================================
//
// PRIVATE METHODS

// send version
// cnt = 0
// max_pack_cnt = count for multiple package send
void SETTINGS::_sendVersion(uint8_t max_pack_cnt) {

	_buffer[0] = _max_settings;
	_buffer[1] = _createCnt(0, max_pack_cnt);
	_buffer[2] = MSB(_version);
	_buffer[3] = LSB(_version);
	_buffer[4] = _type;

	can_com.send(_buffer, 5, CAN_ID_REPLY);

}


// send name
// cnt >= 2
// max_pack_cnt = count for multiple package send
void SETTINGS::_sendName(uint16_t uuid, String name, uint8_t max_pack_cnt, uint16_t can_id) {

	uint8_t pack_cnt;
	uint8_t pos;

	// reset name position
	pos = 0;

	// loop over name packets
	for (pack_cnt = 0; pack_cnt < max_pack_cnt; pack_cnt++) {

		// reset index
		if (uuid > 0) {
			_buffer[0] = MSB(uuid);
			_buffer[1] = LSB(uuid);

			_i = 2;
		}

		else {
			_i = 0;
		}


		// set pack_cnt/max_packets
		_buffer[_i++] = _createCnt(pack_cnt, max_pack_cnt);

		// add name part data
		while (pos < MODULE_NAME_LENGTH && _i < 8) {
			_buffer[_i++] = name[pos++];
		}

		can_com.send(_buffer, _i, can_id);
	}
}


// get cnt/max_cnt
uint8_t SETTINGS::_createCnt(uint8_t cnt, uint8_t max_cnt) {
	return (cnt & 0x0F) << 4 | (max_cnt & 0x0F);
}



// ================================================
//
// STORAGE methods


// buffer: data bytes
// size: count of bytes to collect
// cnt: MSB=cnt, LSB=max packets
bool SETTINGS::readName(uint8_t* buffer, uint8_t size, uint8_t cnt) {

	// collect data
	for (_i = 0; _i < size; _i++) {
		_name[_i + (MSB(cnt) * CAN_NAME_MAX_SIZE)] = buffer[_i];
	}

	// last package => write data
	if ((MSB(cnt) + 1) == LSB(cnt)) {
		_setup.setName(_name);
	}

}


// return name string
String SETTINGS::name(void) {
	return _setup.name();
}


// set name string
void SETTINGS::setName(uint8_t* name) {
	_setup.setName(name);
}


// ================================================
// set light settings 
uint8_t SETTINGS::getByte(uint8_t idx) {
	return _setup.getByte(idx);
}


// set light settings 
uint16_t SETTINGS::getInt(uint8_t idx) {
	return _setup.getInt(idx);
}


// set light settings 
uint32_t SETTINGS::getLong(uint8_t idx) {
	return _setup.getLong(idx);
}


// ================================================
// set light settings 
void SETTINGS::setByte(uint8_t val, uint8_t idx) {
	_setup.setByte(val, idx);
}


// set light settings 
void SETTINGS::setInt(uint16_t val, uint8_t idx) {
	_setup.setInt(val, idx);
}


// set light settings 
void SETTINGS::setLong(uint32_t val, uint8_t idx) {
	_setup.setLong(val, idx);
}
