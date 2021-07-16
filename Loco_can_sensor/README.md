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