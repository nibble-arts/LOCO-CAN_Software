# Module Settings

Each module in the LOCO-CAN system can be accessed via special CAN messages to set internal parameters. The module software version is used to ensure, that the correct values are stored in the correct parameter storage.

The paramters are addressed by an 8-bit address, where the value 0x00 and 0xFF are reserved for special use. Hence 254 different parameter bytes can be used.

The address 0x00 is used to access the module name, while the 0xFF can not be used, because the address for write and reply messages is part of the 8 lower bits of the 11-bit CAN-identifier and the id 0x7FF is reserved for request messages.

## Module Setting Definitions

Each module has an eight bit identification code containing of 3 bits for the module group identification, 4 bits for the module type inside the group and the hightest bit to indicate wireless capability if set to 1.



	Controller 			0x1n
## Settings Protocol

To change the settings of the module the highest CAN identifiers in the range between 0x700 and 0x7FF are used. The messages are devided in three groups for requests, replys and setup data.

For requests and replys bit 8 of the 11-bit identifier has to be 1, for write commands, the bit 8 has to be 0. The identifier ranges are therefore:

* 0x700 to 0x77F 	for writing data
* 0x780 to 0x7FE 	for data reply
* 0x7FF				request message

The UUID is a uinque value, that is created from the internal unique identifier from the microcontroller. The 16-bit value is allways used in big endian format (MSB, LSB).

### Request

A data request is a message to one or all modules with the invitation to send certain data. The request messages contain 0 to 3 bytes of data.

To address a certain module the 16 bit UUID is used. To get a certain settings value a 8 bit index is added. The index values can take on the values between 0x01 and 0xFE (maximum of 254 values). The values 0x00 and 0xFF are not valid and are discarded.

	CAN-ID	byte-0	byte-1	byte-2	byte-3
	 0x7FF	0xFF							global info request
	 0x7FF	UUID-M	UUID-L					info from module (UUID)
	 0x7FF	UUID-M	UUID-L	index 			get settings value[index]
	 0x7FF	UUID-M	UUID-L	index 	 cnt 	value cnt (1-8)

When accessing certain values sending an index, the succeesing 7 bytes are automatically added. If the length of the reply should be reduced, an additional byte count can be added. 

### Reply

When a module is addressed, or a global request was received, a reply message is returned. Depending on the request, the reply can contain different data. Since all CAN messages in the system uses the 29-bit extended form, where the 16 of the 18 additional bits carry the senders UUID, each replying module can be identified.

#### Global info reply

The global reply contains the basic parameters of the module. The control module, that has a webservice for the setup process, will request the data to register the connected modules. The is done in certain time intervals to recoginze newly plugged modules.

The registered plugins are stored with the UUID that automatically is sent with the CAN-identifier, so the parameter setup can be done on each module separately.

The reply message contains:

* The maximal setting count in bytes
* The module software version
* The module name

The global reply message consists of three bytes with metadata about the module message and up to 5 data bytes. When the data size is bigger than 5 bytes, messages follow each other. Byte 1 holds the overall count of the data bytes, while byte-2 contains a value counter for the parts of 5 bytes.

* byte-0	holds the maximum of used setting values (0-254)
* byte-1	the count of packages (bits 4-7) and the package counter (bits 0-3)
* bytes-2/7	six name data bytes

The counter value 0 allways holds the version of the module software.

	CAN-ID 	byte-0	byte-1	byte-2	byte-3 ...
	 0x780	 max 	 0x0m	version	 type	module software version and type
	 0x780	 0xnm 	 name 	  ...	module name (15 bytes)

Version string

	x.y.z

#### Value Reply

When the module is addressed via the UUID a certain value is returned. The modules software version and module type has to be requested using the global request or a request with the module UUID without an data index. 

The reply contains only data values. With the additional count parameter, up to 8 continuing bytes of data can be transmitted in one message.

	CAN-ID 	bytes-0/7
	 0x7nn	  data

### SET Packet

For messages that set values the bit 8 if the 11-bit CAN-identifier has to be set to 0. The index (1-254) is added to the index.

Examples:

	0x701		CAN-ID for index 1
	0x72A		CAN-ID for index 42

The message contains the UUID of the target module and one byte with a package counter. The remaining 5 bytes are used for the data.

	CAN-ID 	byte-0	byte-1	byte-2	bytes-3/7
	 0x700	UUID-M	UUID-L	 cnt 	  name 		set module name
	 0x7ii	UUID-M	UUID-L	 data 				set value[ii]
	 											up to 6 bytes can be added

The counter value 0 allways holds the version of the module software. If the version of the package does not match the module version, the data is ignored.
