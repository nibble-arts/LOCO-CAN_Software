# STATUS

The status LED shows the state of the drive system. It can blink, flash and light in three colours.

* red: indicates an error state
* yellow: the system is in a standby state
* green: the system is in ready state

## Error States (red light)

### CAN EREOR (1) - fast flash

No CAN connection. The heartbeat is not received.

### FATAL ERROR (2) - fast blink

A fatal error state is received from the CAN bus. A controlled immediate shutdown has to be executed.

## Standby States (yellow light)

### MAINS OFF (3) - slow flash

The main power switch is off.

### STANDING (5) - lit

Main power is on, the drive is on and the locomotive is standing.

## Ready Staates (green light)

### Drive Off (4) - slow blink

Main power is on, the drive is off.

### Zero Switch Duty - fast blink

Main power is on. Three drive is in zero duty mode. The control leaver has to be returned to the zero position to clear this state.

### READY (6) - lit

Main power is on, the drive is on and the locomotive is in motion.

# Battery state

If a battery state is received a low voltage status is displayed by clicking all colours alternatingly with red. The states are changed to:

* red flash -> red flash two times
* red blink -> blink two times fast
* x flash -> flash x/red
* x blink -> blink x/red