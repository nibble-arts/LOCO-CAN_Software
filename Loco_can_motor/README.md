# LOCO-Motor
With the LOCO-Motor module all types of power drivers can be acceesed via the CAN bus. The setup of the motor software can be adapted to a wide variety of motor control drivers. With the additional light and horn outputs a locomotive control can be set up with a control and a motor module.

The internal motor voltage is sent as CAN_ID_MOTOR_VOLTAGE to the bus as well as two battery measurement inputs, that provide the state of up to two batteries connected in series.

## V2.2-s
In the version V2.2 a connector for battery voltage measurement is implemented. The two leads can be used to measure two batteries connected in series.

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

### Battery voltage
In the standard settings battery voltage 1 is relative to GND, battery voltage 2 relative to battery 1. The voltage message sends three values for overall voltage (CAN_ID_BATT_VOLTAGE), voltage 1 (CAN_ID_BATT_1_VOLTAGE) and voltage 2 (CAN_ID_BATT_2_VOLTAGE).

Jack: 2-pin JST-PH connector
| pin | usage     |
|:----|:----------|
| 1   | Battery 1 |
| 2   | Battery 2 |

### FTDI Interface
Standard 5-pin FTDI Interface


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
