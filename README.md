
# LOCO-CAN

The hardware schematics and PCB layouts are managed in the [LOCO-CAN_Harware](https://github.com/nibble-arts/LOCO-CAN_Hardware) repository.

The LOCO-CAN-system is designed for the use is miniature railway vehicles. It provides a CAN-bus connecting the different modules inside a locomotive, but also between vehicles in a train.

The system is still under developement. The CAN-specification is defined but can be extended. Board designs are available in different versions, due to the process of evolvement. Besides bugs in the board design details like the pinout of the program interface differ between the versions.

## LOCO-CAN System Description

The Modules are connected with 4-pin cables using MICRO MATE-N-LOK connectors. The cables have a supply line with a voltage of +6 up to +30 Volts. The supply can be provided through some modules, that have got supply connectors (vertical 2-pin MICRO MATE-N-LOK connector). The motor module supplies directly from the motor driver.

All supply connectors have a diode, so the input voltages on places in the network can be different. The supply voltage on the bus will be the highest value. The operation voltage for internal function of the modules is created onboard.

So it is possible to connect two locomotives with 12 Volt and 24 Volt batteries without any problem. All connected units have a common GND level. When using the CAN-supply for LED-lights, it is important to have the big voltage range in mind. Best is to use a current regulator for the LEDs.

**It is not recommended to use the CAN-Connector for supply of the bus.**

## ICP SDI pads
To flash the bootloader on Atmega chips latter versions provide three pads to access the SDI port of the MCU. A jumper in the CS line between the MCU and the CAN controller has to be closed after the flash process.

The hardware versions with the SDI pads are marked with a letter s at the end of the version string.

# Modules
All modules are equipped with two 4-pin CAN connectors. The following modules are available or in developement:

## Interface definitions
The pinout of the FTDI interface for flashing new software differs in the early versions. The standard pinout will be implemented in all revisions, divergent pinouts are listed with the version descriptions.

All versions are compatible on the CAN-bus, the differences are only in the expansion ports.

Standard FTDI Interface to flash software updates
| pin | usage     |
|:----|:----------|
| 1   | **1 DTS** |
| 2   | **2 RX**  |
| 3   | **3 TX**  |
| 4   | **4 3V3** |
| 5   | **GND**   |


# LOCO-Control
The controller module provides connectors to apply pots, switches, leds and meters in an easy way to implement an own controller design.

The analog switch inputs use a potentiometer or a switch with applied resistors to change the voltage on the analog input. The software can learn the distinct positions and map them to discrete switch positions.

The connectors for volt and ampere display provide either an analog value (PWM) or a model servo signal. The servo can be used to build a analog gauge for display.

## Hardware version V2.0a-s

### Power out
The 5-Volt output can be used to supply additional electronic inside the controler with up to 500mA.

**2-pin JST-PH connector**
| pin |      |
|:----|:-----|
|  1  | +5V  |
|  2  | GND  |

### Control Input
**3-pin JST-PH connectors**
| DRIVE    | BREAK    | MAINS    | DIR       | TALLY   |
|:---------|:---------|:---------|:----------|:--------|
| 1	GND	   | 1 GND    | 1 GND	 | 1 GND     | 1 RED   |
| 2	POT    | 2 POT    | 2 SWITCH | 2 SWITCH  | 2 GND   |
| 3 VCC	   | 3 VCC    | 3 VCC    | 3 VCC     | 3 GREEN |

### Meters
**2x3 pinheader**
*VOLTMETER		AMMETER*
| 1 Volt   | 2 Ampere |
|:---------|:---------|
| 3 VCC    | 4 VCC    |
| 5 GND    | 6 GND    |

### Auxilary IO
**6-pin JST-PH connector**
*Aux I/O*
| pin |             |
|:----|:------------|
| 1   | IO1         |
| 2   | IO2         |
| 3   | IO3         |
| 4   | IO4         |
| 5   | Analog 1    |
| 6   | Analog 2    |

### FTDI Interface
| V2.0     | V2.0a     |
|:---------|:----------|
| 1 DTS    | **1 DTS** |
| 2 **TX** | **2 RX**  |
| 3 **RX** | **3 TX**  |
| 4 3V3    | **4 3V3** |
| 5 GND    | **5 GND** |


# LOCO-Motor
With the LOCO-Motor module all types of power drivers can be acceesed via the CAN bus. The setup of the motor software can be adapted to a wide variety of motor control drivers. With the additional light and horn outputs a locomotive control can be set up with a control and a motor module.

## V2.1a/V2.1b-s
The versions only differ in the pinout of the FDTI-interface.

### Motor driver
Plug: MATE-N-LOK 1-794617-0
Jack: MATE-N-LOK 4-794618-0

| pin | usage       | pin | usage       |
|:----|:------------|:----|:------------|
| 1   | +12V IN     | 2   | Light       |               
| 3   | DRIVE       | 4   | HORN        |
| 5   | BREAK       | 6   | MOTOR VOLT+ |
| 7   | FORWARD     | 8   | MOTOR VOLT- |
| 9   | REVERSE     | 10  | GND         |

Pins 6 and 8 are connected to the motor output to sense the voltage. Drive and break outputs provide a PWM signal to drive the power output stage.

### FTDI Interface
| V2.1a    | V2.1b     |
|:---------|:----------|
| 1 DTS    | **1 DTS** |
| 2 **TX** | **2 RX**  |
| 3 **RX** | **3 TX**  |
| 4 3V3    | **4 3V3** |
| 5 GND    | **5 GND** |


# LOCO-Light
With the light module different lights can be controlled. Each output ca drive up to 3 Ampere, when using the external +12V input with the version greater V2.1. With the V2.0 only the maximum output current of the CAN-bus can be used.


###CAN light stati
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



# LOCO-Sensor
The sendor module provides four voltage inputs and a current measurement up to 30 Ampere. In addition a speed/pulse input is provided.

## Hardware version V2.1/V2.1a/V2.1a-s
The versions differ in the pinout of the FDTI-interface. Both versions V2.1a and V2.1a-s offers the SDI pads.

### Voltage
The pins can provide absolute values reffered to GND, or relative values between two pins, depending on the module setup.

| pin | usage     |
|:----|:----------|
| 1   | Voltage 1 |
| 2   | Voltage 2 |
| 3   | Voltage 3 |
| 4   | Voltage 4 |

### Current
The current measurement connectors are thwo 6mm holes outside of the casing. The direction of the current is provided as positive or negative values. The ratio of the positive direction to the connection on the pins, can be set in the setup.

### Speed/pulse
See in the Connector section below.

### FTDI Interface
| V2.1     | V2.1a     |
|:---------|:----------|
| 1 DTS    | **1 DTS** |
| 2 **TX** | **2 RX**  |
| 3 **RX** | **3 TX**  |
| 4 3V3    | **4 3V3** |
| 5 GND    | **5 GND** |


## LOCO-Servo

### V2.0/V2.1a-s
The versions only differ in the pinout of the FDTI-interface.

### FTDI Interface
| V2.0     | V2.1a-s   |
|:---------|:----------|
| 1 DTS    | **1 DTS** |
| 2 **TX** | **2 RX**  |
| 3 **RX** | **3 TX**  |
| 4 3V3    | **4 3V3** |
| 5 GND    | **5 GND** |


## Universal
These modules offer an unallocated connector for universal use. 

### V1.0
The first prototype board using DIL packages and JST-PH connectors for the CAN-bus. **Although this version is compatible with the system, it is no longer supported!**

**Extension bus: 10x1 pins**
| pin         | usage        |
|:------------|:-------------|
| 1  VCC      |              |
| 2  D9 (PWM) | METER_AMP    |
| 3  D8       | METER_VOLT   |
| 4  D7       | STATUS_GREEN |
| 5  D6 (PWM) | STATUS_RED   |
| 6  A0       | ANALOG_DRIVE |
| 7  A1       | MAINS_SWITCH |
| 8  A2       | DIR_SWITCH   |
| 9  A3       | LIGHT_SWITCH |
| 10 GND      |              |

### V1.2

The second prototype board using DIL packages and an bigger extension bus. It was never produced. **Although this version is compatible with the system, it is no longer supported!**

**Extension bus: 8x2 pins**
| pin         | usage             | pin         | usage              |
|:------------|:------------------|:------------|:-------------------|
| 1  VCC      |                   | 2  D2       |                    | 
| 3  A5       |                   | 4  D3 (PWM) |                    |
| 5  A4       |                   | 6  D4       |                    |
| 7  A3       |                   | 8  D5 (PWM) |                    |
| 8  A2       |                   | 10 D6 (PWM) | STATUS_RED         |
| 11 A1       |                   | 12 D7       | STATUS_GREEN       |
| 13 A0       |                   | 14 D8       | METER_VOLT (Servo) |
| 15 D9 (PWM) | METER_AMP (Servo) | 16 GND      |                    |

**big extension bus version: 9x2 pins**
| pin         | usage             | pin         | usage              |
|:------------|:------------------|:------------|:-------------------|
| 17  +12V    |                   | 18 GND      |                    | 

### FTDI Interface
Both versions provide the default FTDI pinout.
| pin | usage     |
|:----|:----------|
| 1   | **1 DTS** |
| 2   | **2 RX**  |
| 3   | **3 TX**  |
| 4   | **4 3V3** |
| 5   | **GND**   |


## LOCO-WIFI (universal)
The LOCO-WIFI is a universal module with two extension busses besides the two CAN connectors. It can establish a wireless connection via WIFI and Bluetooth. 

### V2.1
The ESP32 boards are shipped with a bootloader and do not need the SPI flash pads.

| **IO 1**           | **IO 2**             |
|:-------------------|:---------------------|
| **9x1 pins**       | **5+4x1 pins**       |
| 1 +3,3V            | 1 VCC (12V)          |
| 2 IO27             | 2 IO4                |
| 3 IO26             | 3 IO0 (GND to Flash) |
| 4 IO25             | 4 IO2                |
| 5 IO33             | 5 IO15               |
| 6 IO32             |                      |
| 7 IO35             | 1 IO13               |
| 8 IO34             | 2 IO12               |
| 9 GND              | 3 IO14               |
|                    | 4 GND                |

### FTDI Interface
The version provide the default FTDI pinout. To flash a new software version, pin 3 of the 5-pin IO 2 must be connected to GND before power up.

| pin | usage     |
|:----|:----------|
| 1   | **1 DTS** |
| 2   | **2 RX**  |
| 3   | **3 TX**  |
| 4   | **4 3V3** |
| 5   | **GND**   |


### LOCO-Splitbox
The splitbox is a tiny module that split up the CAN-bus line with three connectors. It also provides a power input connector for additional supply of the bus.

For details ot the connector pinouts see the connector section below.

**Power for the system has to be provided via a motor module or the splitboxes. It is not recommended to use the CAN connector for this purpose!**


# Hardware

## Wired units
| Unit            | Type            |
|:----------------|:----------------|
| Processor       | Atmega 328P     |
| CAN-Controller  | MCP 2515        |
| CAN-Transceiver | MCP 2551        |

## Wireless units
| Unit            | Type            |
|:----------------|:----------------|
| Processor       | ESP32           |
| CAN-Controller  | integrated      |
| CAN-Transceiver | MCP 2551        |


# Connectors
The following connectors for the basic IOs are universal used by all modules if needed.

## CAN bus
The CAN-bus is found on all modules, even the WIFI. It connects all modules and provides both communication and supply.

**4-pin 2x2**
Plug: MATE-N-LOK 794617-4
Jach: MATE-N-LOK 3-794618-4

| pin | usage                      |
|:---:|:---------------------------|
| 1   | GND                        |
| 2   | CAN-L                      |
| 3   | CAN-H                      |
| 4   | +6-30 Volt / max. 5 Ampere |

##Pulse
Used for speed or rpm measurement.

**2-pin horizontal**
Plug: MATE-N-LOK 2-1445055-2
Jack: MATE-N-LOK 1445022-2

| pin | usage |
|:---:|:------|
| 1   | Pulse |
| 2   | GND   |

**Power**
Supply input for the LOCO-system.

**2-pin vertical**
Plug: MATE-N-LOK 794617-2
Jack: MATE-N-LOK 3-794618-2

| pin | usage                      |
|:---:|:---------------------------|
| 1   | +6-30 Volt / max. 5 Ampere |
| 2   | GND                        |
