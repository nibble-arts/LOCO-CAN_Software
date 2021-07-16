# LOCO-Light
With the light module different lights can be controlled. Each output ca drive up to 3 Ampere, when using the external +12V input with the version greater V2.1. With the V2.0 only the maximum output current of the CAN-bus can be used.


### CAN LIGHT_STATUS (1 byte package)
The lights are controlled by the light_status message (CAN_ID_LIGHT). The module sends back the overall current of the connected and activated lights (CAN_ID_LIGHT_CURRENT).

The can protocol supports eight light stati in out byte, that can be mapped to the six output lines in the module setup. To activate a status, the corresponding bit has to be set to 1.

	bits     7      6      5      4      3      2      1      0
	       	main  train   cab   instr   back    high   low   posit
	       	------------------------------------------------------
	main:	main light switch
	train:	train lights
	cab:		cabine light
	instr:	instrument light
	back:	back light
	high:	bright spot light
	low:		low spot light
	posit:	position light

A common current sensor returns the overall consumption of the light outputs.

The versions differ in the pinout of the light connector and the FDTI-interface.

## Light connector
Degson DG308-2.54-08P-14-00AH
or
JST XH

## Hardware version V2.0
| pin | usage      |
|:----|:-----------|
| 1   | Light 1    |
| 2   | Light 2    |
| 3   | Light 3    |
| 4   | Light 4    |
| 5   | Light 5    |
| 6   | Light 6    |
| 7   | GND        |

## Hardware version V2.1a/V2.1a-s
| pin | usage      |
|:----|:-----------|
| 1   | +12V       |
| 2   | Light 1    |
| 3   | Light 2    |
| 4   | Light 3    |
| 5   | Light 4    |
| 6   | Light 5    |
| 7   | Light 6    |
| 8   | GND        |

### FTDI Interface
| V2.1     | V2.1a     |
|:---------|:----------|
| 1 DTS    | **1 DTS** |
| 2 **TX** | **2 RX**  |
| 3 **RX** | **3 TX**  |
| 4 3V3    | **4 3V3** |
| 5 GND    | **5 GND** |


# LOCO-Single Light
**To do**
A tiny module with only one CAN connector and one FET driven output for a single light. It can be used for intelligent back lights. In this case, a backlight heartbeat status can detect the train integrity.


## Settings
A mapping table applies the six outputs to the eight light stati. In addition the drive message (CAN_ID_DRIVE) can be used to switch depending on the selected direction.

### Mapping

	byte		content
	dir = 0
	 0		forward_light 1
	 1		forward_light 2
	 2		forward_light 3
	 3		forward_light 4
	 4		forward_light 5
	 5		forward_light 6
	 6		forward_light 7
	//
	dir = 1
	 7		backward_light 1
	 8		backward_light 2
	 9		backward_light 3
	 10		backward_light 4
	 11		backward_light 5
	 12		backward_light 6
	 13		backward_light 7