
# LOCO-CAN System Description

The Modules are connected with 4-pin cables using MICRO MATE-N-LOK connectors. The cables provide a supply line with a voltage of +6 up to +30 Volts. The supply can be provides through some modules, that have got supply connectors (vertical 2-pin MICRO MATE-N-LOK connector). The motor module can get supply directly from the motor driver.

All supply connectors have a diode, so the input voltages on places in the network can be different. The supply voltage on the bus will be the highest value.

So it is possible to connect two locomotives with 12 Volt and 24 Volt batteries without any problem. All connected units have a common GND level. When using the CAN-supply for LED-lights, it is important to have the big voltage range in mind. Best is to use a current regulator for the LEDs.

It is not recommended to use the CAN-Connector for supply of the bus.

## Modules

The following modules are available or in developement:

### Controller

The controller module is designed to realize a cable command unit. It offers connectors for potentiometers, switches and LEDs.

	DRIVE       3-pin pot input
	BREAK       3-pin pot input
	MAINS       3-pin analog switch input
	DIR         3-pin analog switch input
	I/O         6-pin (4x digital, 2x analog)
	VOLT        3-pin analog/servo connector
	AMPERE      3-pin analog/servo connector

The analog switch inputs use a potentiometer or a switch with applied resistors to change the voltage on the analog input. The software can learn the distinct positions and map them to discrete switch positions. 

The connectors for volt and ampere display provide either an analog value (PWM) or a model servo signal. The servo can be used to build a analog gauge for display. 

### Switch / Light
Klemmleiste: Degson DG308-2.54-08P-14-00AH
oder
JST XH gewinkelt

### Sensor

### Motor Control
Stecker: MATE-N-LOK 1-794617-0
Buchse: MATE-N-LOK 4-794618-0

	1   +12V IN     2   Light               
	3   DRIVE       4   HORN
	5   BREAK       6   MOTOR VOLT+
	7   FORWARD     8   MOTOR VOLT-
	9   REVERSE     10  GND

Pins 6 and 8 are connected to the motor output to sense the voltage. Drive and break output a PWM to drive the power output stage.

### Single Light

### Splitbox

The splitbox is a tiny module that can be used to split up the CAN-bus line. It also provides a Power input connector for additional supply of the bus.

## Hardware

Processor:          Atmega 328P
CAN-Controller:     MCP 2515
CAN-Transceiver:    MCP 2551

### Connectors

#### CAN-Bus
Stecker: MATE-N-LOK 794617-4
Buchse: MATE-N-LOK 3-794618-4

	1   +6-30 Volt / max. 5 Ampere
	2   CAN-H
	3   CAN-L
	4   GND

#### Power
Stecker: MATE-N-LOK 794617-2 (2-pin vertical)
Buchse: MATE-N-LOK 3-794618-2

	1 +6-30 Volt / max. 5 Ampere
	2 GND

#### Digital Sensor
i.e. Speed
Stecker: MATE-N-LOK 2-1445055-2
Buchse: MATE-N-LOK 1445022-2

	1   Digital in
	2   GND