# LOCO-Wiki CAN Protocol

The protocol uses the 29-bit extended CAN-identifier for all messages with the basic 11 bits as group identifier and the 18 extended bits for the device UUID. The group bits are used in the following way:

## ID & UUID
The ID defines the type of message while the UUID is the unique identification of a node unit. With the UUID messages of the same type from a receiving node it can be distinguished, if this certain message is ment for it. Messages ment for all devices (train light) can discard the UUID and only use the group identification.

### 10-8 Message Priority (max 8)
The highest 3 bits define the priority for the messages. The highest value 0x7 with the least priority is used for node setup messages.

### 7-4 Device Type (max 15)
The mid 4 bits define the device types. Null is not used.

### 0-3 Device Subtype (max 15)
The least 4 bits define the subtype of the device. Null is not used.

## Device Types and Subtypes
* Input
    - Controller (complex message)
    - Switch
    - Pot
* Display
    - Lamp
    - Display
* Actuator
    - Speed
    - Direction
    - Position
    - Relais
* Sensor
    - Current
    - Voltage
    - Frequenzy


## CONTROL Commands
The control commands contain control messages for the system, like the system status or speed and direction values.

### 0x0nm   High Priority Command
* Emergency stop    (f=0x000)

### 0x2nm   Mid Priority Command
0. speed            (f=0x20f)
1. Break            (f=0x21f)
2. direction        (f=0x22f)
3. Horn             (f=0x23f)

### 0x4nm   Low Priority Command
0. Licht            (f=0x40f)
1. Switch           (f=0x41f)

## VALUE Commands
The value commands send measurement values to the system. Currernt values are high priority to be used for protection.

### 0x1nm      High Priority Value
0. Battery current (main current)   (f=0x10f)
1. Motor Current                    (f=0x11f)
2. Light current                    (f=0x12f)

### 0x3nm       Low Priority Value
0. Battery voltage (main voltage)   (f=0x30f)
1. Motor voltage                    (f=0x31f)
2. Tacho                            (f=0x32f)


## PROGRAM Commands

### 0x7nm                           (f=0x7ff)


# STATUS

DATA

7 byte package

STATUS
byte 0:   7      6      5      4      3      2      1      0
        error  ready   stop                 dir   drive  mains

DRIVE VALUE: 10-bit value of drive voltage
byte 1: drive bit 8-9
byte 2: drive bit 0-7

POWER VALUE: 10-bit value of drive max power
byte 3: power bit 8-9
byte 4: power bit 0-7

BREAK VALUE: 10-bit value of break intensity
byte 5: break bit 8-9
byte 6: break bit 0-7


# LIGHT

LIGHT DATA

1 byte package

LIGHT_STATUS
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
