# DIL Version V1.0

## Issues
1. Atmega 328 to MCP2515 connection has to be corrected to:

* Atmega (MOSI) pin 17 - MCP2515 (SI) pin 14
* Atmega (MISO) pin 18 - MCP2515 (SI) pin 15

2. ICP-Reset missing

* Connect Atmega (RESET) pin 1 with serial 100n to DTR of program unit


## Bus-Connector
10x1 PIN (2,54mm Raster)

1   VCC
2   D9
3   D8
4   D7
5   D6
6   A0
7   A1
8   A2
9   A3
10  GND

## ICP-Connector
4x1 PIN (2,54mm Raster)
Mitte: 1200/600

1   VCC
2   TX
3   RX
4   GND

corrected (siehe issues):

1   VCC
2   TX
3   RX
4   DTR
5   GND

# CAN-Connector Micro MATE-N-LOC 3mm Raster
1   VCC
2   CAN-H
3   CAN-L
4   GND



# SMD-Verions 2.x

Wenn nicht anders angegeben: 1/100"

## Board
Maße 1300 x 1200
Löcher: D=3mm 100/100 1200/100 1200/1100 100/1100

## Bus-Connector
8x2 PIN (2,54mm Raster)
Mitte: 150/600

1   VCC     2   D2
3   A5      4   D3
5   A4      6   D4
7   A3      8   D5
9   A2      10  D6
11  A1      12  D7
13  A0      14  D8
15  D9      16  GND100

## ICP-Connector
6x1 PIN (2,54mm Raster)
Mitte: 1200/600

1   DTR
2   TX
3   RX
4   VCC
5   CTS
6   GND

# CAN-Connector Micro MATE-N-LOC 3mm Raster
1   VCC
2   CAN-H
3   CAN-L
4   GND


# Dimensions DIL-Version 1.2

Wenn nicht anders angegeben: 1/100"

## Board
Maße 2250 x 1550
Löcher: D=3mm 100/100 2150/100 2150/1450 100/1450

## Bus-Connector
8x2 PIN (2,54mm Raster)
Mitte: 1225/875

1   VCC     2   D2
3   A5      4   D3
5   A4      6   D4
7   A3      8   D5
9   A2      10  D6
11  A1      12  D7
13  A0      14  D8
15  D9      16  GND

## ICP-Connector
6x1 PIN (2,54mm Raster)
Mitte: 625/125

1   DTR
2   TX
3   RX
4   VCC
5   CTS
6   GND

# CAN-Connector JST-XH 2,5mm Raster
1   VCC
2   CAN-H
3   CAN-L
4   GND
