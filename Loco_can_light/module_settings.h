/*
The settings for a module are managed by the settings class. Each value is
registered in the settings class on boot and can be accessed by the settings
id or the value type.

All settings values are stored in the EEPROM and loaded on boot time and are
available from the RAM. Changes via the CAN setup messages are stored in the EEPROM
and updated and the RAM copy is reloaded after this action.

Each value declaration is a 16 bit value with the format:
	bits 0-3 = size in bytes
	bits 4-7 = command type

The settings constant contains the value declarations and sepcifies the order of
the setting ids.
*/


// settings declaration
#define MODULE_LIGHT_DIR 0x0001

#define MODULE_LIGHT_FORW_1 0x1001
#define MODULE_LIGHT_FORW_2 0x1101
#define MODULE_LIGHT_FORW_3 0x1201
#define MODULE_LIGHT_FORW_4 0x1301
#define MODULE_LIGHT_FORW_5 0x1401
#define MODULE_LIGHT_FORW_6 0x1501
#define MODULE_LIGHT_FORW_7 0x1601
#define MODULE_LIGHT_FORW_8 0x1701

#define MODULE_LIGHT_REW_1 0x2001
#define MODULE_LIGHT_REW_2 0x2101
#define MODULE_LIGHT_REW_3 0x2201
#define MODULE_LIGHT_REW_4 0x2301
#define MODULE_LIGHT_REW_5 0x2401
#define MODULE_LIGHT_REW_6 0x2501
#define MODULE_LIGHT_REW_7 0x2601
#define MODULE_LIGHT_REW_8 0x2701


// settings declaration constant
static const uint16_t settings_declaration[] = {
	MODULE_LIGHT_DIR,
	MODULE_LIGHT_FORW_1,
	MODULE_LIGHT_FORW_2,
	MODULE_LIGHT_FORW_3,
	MODULE_LIGHT_FORW_4,
	MODULE_LIGHT_FORW_5,
	MODULE_LIGHT_FORW_6,
	MODULE_LIGHT_FORW_7,
	MODULE_LIGHT_FORW_8,
	MODULE_LIGHT_REW_1,
	MODULE_LIGHT_REW_2,
	MODULE_LIGHT_REW_3,
	MODULE_LIGHT_REW_4,
	MODULE_LIGHT_REW_5,
	MODULE_LIGHT_REW_6,
	MODULE_LIGHT_REW_7,
	MODULE_LIGHT_REW_8
};
