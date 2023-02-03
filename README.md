# LOCO-CAN

The hardware schematics and PCB layouts are managed in the [LOCO-CAN](https://github.com/nibble-arts/LOCO-CAN_Hardware) repository.

The system is still under developement.

The LOCO-CAN-system is designed for the use is miniature railway vehicles. It is based on the CAN-bus to connect the different modules inside a locomotive, but also between vehicles in a train.

The CAN protocol definitions can be extended to add new functionality. Board designs are available in different versions, due to the process of evolvement. Besides bugs in the board design details like the pinout of the program interface differ between the versions and the electric spezifications of the CAN-connector. The communication protocal is compatible betweet all versions.


## Design
The design is highly modular. For the simple control of aa elektric locomotive only a control and a motor module is needed. When using the latest motor module version values for motor voltage and battery voltage is sent to the can bus. The control module has the ability to connect meters for display of this values.

The structure with a bus system makes it easy to expand the contruction with additional functions. New modules, i.e. for light, controlling servos or measuring corrent, only need to be hooked into the CAN-line.


# Configuration
**This functionality is not yet implemented**
The modules are shipped with a standard configuration like the assignment of the switch module outputs to the light stati or the potentiometer value for neutral position of the throtle. The paramters can be adjusted using the webinterface of a WiFi-modul. Connecting with a laptop or smartphone gives access to a user-friendly interface for this task.

## Software Updates
The pinout of the FTDI interface for flashing new software differs in the early versions. The standard pinout will be implemented in all revisions, divergent pinouts are listed with the version descriptions.

All versions are compatible on the CAN-bus, the differences are only in the expansion ports.

Standard FTDI Interface to flash software updates
| pin | usage     | cable  |
|:----|:----------|--------|
| 1   | **1 DTS** | yellow |
| 2   | **2 RX**  | braun  |
| 3   | **3 TX**  | white  |
| 4   | **4 3V3/5V** | green  |
| 5   | **GND**   | GND    |

For in circuit programming four measuring points are implemented. Only the last version has an additional point for a reset.

ICP-Interface
| pin | usage |
|:----|:------|
| 1   | SCK   |
| 2   | SI    |
| 3   | SO    |
| 4   | RST   |

## CAN Software Updates
**This functionality should be implemented in the future**
A future update should bring the ability for a software update using the CAN-bus instead of the serial port. The update process is initialized and controlled by a WiFi-module. Using the webinterface the new firmware for a module type is loaded in the WiFi-module.

All connected modules with this type get a command to enter the CAN-bootloader. The update command sets the update bit in the CAN-bootloader as well as the count of received and saved packages in the EEPROM. If the update process is terminated, it can be restarted at the last package that was received.

The CAN-bootloader communicates with the sending WiFi module using a handshake for each package. The WiFi module waits for the reply of all modules that are in the update process for the next package to be sent.

When finished all updated modules reset the update bit and restart automatically.


# Modules
The modules are intendet for a special use, like switching light or controlling a motor. All modules are equipped with two CAN connectors. A detailed description is found in the README.md file in the corresponding subdirectories.

Beside the spezialized modules universial versions with a general I/O connectors can be used for different tasks. Two versions with compatible extension connectors are available, one with wireless capability, witch is based on the more powerfull 32 bit ESP32 processor.


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


# LOCO-Control-Adapter
The controller module provides connectors to apply pots, switches, leds and meters in an easy way to implement an own controller design.

The analog switch inputs use a potentiometer or a switch with applied resistors to change the voltage on the analog input. The software can learn the distinct positions and map them to discrete switch positions.

The connectors for volt and ampere display provide either an analog value (PWM) or a model servo signal. The servo can be used to build a analog gauge for display.

The control module consists of an universal module providing CAN-bus connectors and an optional wireless connection (LOCO-Universal, LOCO_WiFi), that is piggipacket on a adapter board. The adapter creates a +5 Volt supply for all controls from the CAN-supply lines and offers JST-PH connectors for the switches, pots and LEDs.

## Hardware version V2.1


### Power out
The 5-Volt supply output can be used to supply additional electronic inside the controler with up to 500mA.

### DRIVE / BREAK / POWER
Three pot inputs for drive, break and power regulators.

**3-pin JST-PH connectors**
| DRIVE    | BREAK    | POWER    |
|:---------|:---------|:---------|
| 1	GND	   | 1 GND    | 1 GND	 |
| 2	POT    | 2 POT    | 2 SWITCH |
| 3 VCC	   | 3 VCC    | 3 VCC    |

### DIR / MAINS
Two analog switch inputs for direction and mains.

**3-pin JST-PH connectors**
| DIR      | MAINS    |
|:---------|:---------|
| 1	GND	   | 1 GND    |
| 2	POT    | 2 POT    |
| 3 VCC	   | 3 VCC    |

### V-BATT / V-MOT / AMP
Three servo/analog outputs for analog meters. The output type is either a model servo or a pwm signal.

**3-pin JST-PH connectors**
| BATTERY  | MOTOR    | AMPERE   |
|:---------|:---------|:---------|
| 1	OUT    | 1 OUT    | 1 OUT    |
| 2 VCC	   | 2 VCC    | 1 VCC    |
| 3	GND	   | 3 GND    | 1 GND    |

### STATUS
The dual color LED (green/red with common GND) is conneted to this port.

**3-pin JST-PH connectors**
| pin | usage |
|:----|:------|
| 1   | red   |
| 2   | GND   |
| 3   | green |

### INST
The instrument light output provides a +5V/+12 Volt supply for lighting the instruments. It is powered by the CAN-bus line and therefore can only use the maximum of 5 Ampere. The FET-ouput is designet to switch this current, but it is recommended to use LEDs with much less power consumption, especially when the WiFi controller is powered by a battery.
To select the voltage a connection between the voltage and the center off jumper JP1 has to be soldered.

**3-pin JST-PH connectors**
| pin | usage      |
|:----|:-----------|
| 1   | +5V/+12V   |
| 2   | Lights     |
| 3   | GND        |

### SIGNAL
The signal connector has two inputs for a high/low horn operation. Setting both inputs to low, activates the bell function.
**3-pin JST-PH connectors**
| pin | usage |
|:----|:------|
| 1   | high  |
| 2   | low   |
| 3   | GND   |


# Hardware

## Power Supply

The Modules are connected with 4-pin cables using MICRO MATE-N-LOK connectors. The cables have a supply line with a voltage of +6 up to +30 Volts. The supply can be provided through the modules that have got supply connectors (vertical 2-pin MICRO MATE-N-LOK connector). The motor module supplies directly from the motor driver.

All supply connectors have a diode, so the input voltages on places in the network can be different. The supply voltage on the bus will be the highest value. The operation voltage for internal function of the modules is created onboard.

So it is possible to connect two locomotives with 12 Volt and 24 Volt batteries without any problem. All connected units have a common GND level. When using the CAN-supply for LED-lights, it is important to have the big voltage range in mind. Best is to use a current regulator for the LEDs.

**It is not recommended to use the CAN-Connector for supply of the bus.**


### LOCO-Splitbox
The splitbox is a tiny module that split up the CAN-bus line with three connectors. It also provides a power input connector for additional supply of the bus.

For details ot the connector pinouts see the connector section below.

**Power for the system has to be provided via a motor module or the splitboxes. It is not recommended to use the CAN connector for this purpose!**


## ICP SDI pads
To flash the bootloader on Atmega chips latter versions provide three pads to access the SDI port of the MCU. A jumper in the CS line between the MCU and the CAN controller has to be closed after the flash process.

The hardware versions with the SDI pads are marked with a letter s at the end of the version string.


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
Jack: MATE-N-LOK 3-794618-4

| pin | usage                      |
|:---:|:---------------------------|
| 1   | GND                        |
| 2   | CAN-L                      |
| 3   | CAN-H                      |
| 4   | +6-30 Volt / max. 5 Ampere |

**4-pin Mini-XLR**
For the connection between vehicles the 4-pin Mini-XSL connectors are used. The cables are equiped with male type connectors
on both ends. Although the CAN-bus is very resistant to electrical interferences, a shielded cable is strongly recommended.
The shielding has to conneected to the GND pin.

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
