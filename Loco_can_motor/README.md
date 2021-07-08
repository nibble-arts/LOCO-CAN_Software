# LOCO-CAN MOTOR-Module

The motor module is used to control a motor driver.

## Connections

* PWM-Drive
* PWM-Break
* Forward
* Reward
* Mains

* Motor voltage
* [Motor current]

## Basic Requirements
For the operation two basic requirements must be fulfilled, a stable CAN-connection and a controller signal. If not, the motor control is set to stop.

### CAN alive
The CAN heartbeat must be present. The heartbeat listens to all CAN messages that have to be repeated in not more than the time set in the HEARTBEAT value (500ms). 

### CONTROLLER connected
A controller signal must be received to enable the motor device operation. Only one controller can operate at a time.

Only one controller can send drive messages at a time. To ensure, that wrong messages are ignored, the UUID of the first received message is stored and used for filtering. 

### POWER ON
When the two basic requirements are fullfilled the power can be switched on.

    can_alive == true
    drive_signel == true

### DRIVE ON

    drive_message.drive == true
        switch on drive

        // DRIVE ON
            // DRIVE ZERO
                // direction change
            // DRIVE active 
                // direction fixed

        // 
### Mains OFF

