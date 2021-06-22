# Software Design Rools

## Global settings
The global setup files loco_config.h holds the basic definitions for the whole project and the can_protocol.h file the CAN-bus protocol definitions. Both files have to be linked to the module directory. 

In the config.h file the global files are included and local definitions for the module. The CAN protocal definitions must only be included when used in the file.

## File Structure
The module software is split into separate files:

* main_file.ino     startup and main loop
* module.cpp        module specific methods

Additional functions should be implemented as classes.

In the main file setup routine starts the serial debug port, the CAN communication with the read filters and initializes the module.

The main routine calles the module update method.