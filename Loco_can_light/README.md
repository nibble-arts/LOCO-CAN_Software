# LOCO-Light

The module can switch six output with a maximum current of 3 Ampere per line. The poitive supply for the lights have to be applied from the battery, if the overall current exceeds the 5 Ampere of the CAN supply.

## CAN messages
The lights are controlled by the light_status message (CAN_ID_LIGHT). The module sends back the overall current of the connected and activated lights (CAN_ID_LIGHT_CURRENT).

**LIGHT_STATUS (1 byte package)**

	byte 0:   7      6      5      4      3      2      1      0
			main  train   cab   instr   back    high   low   posit

main:    main light switch
train:   train lights
cab:     cabine light
instr:   instrument light
back:    back light
high:    bright spot light
low:     low spot light
posit:   position light

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