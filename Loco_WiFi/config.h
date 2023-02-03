/*
 * Loco Wifi Control configuration
 * @autor: Thomas Winkler
 * @copyright: 2019-11-17
 * @lizence: CC0
 */

#ifndef CONFIG_H
#define CONFIG_H

/*
 * list of boards
 */
#define BOARD_WIFI_V_2_1 1 // WIFI V2.1
#define BOARD_UNIV_V_2_1 2 // UNIVERSIAL V2.1


#define BOARD_DEVKIT_V1 1
#define BOARD_LOLIN_D32 2
#define BOARD_CONTROL_V2_0 3


/*
 * select correct motherboard from list above
 */
#define BOARD_VERSION BOARD_CONTROL_V2_0
#define SOFTWARE_VERSION 0x0010


/*
 * WIFI server configuration
 */
#define WIFI_AP_MODE false


#define WIFI_SSID "Toms-2.5G"
#define WIFI_PASSWORD "MbkPm2020"
#define WIFI_PORT 80

#define AP_SSID "Loco WIFI Control"
#define AP_PASSWORD "123456789"
#define AP_PORT 80


/*
 * HTTP parameter settings
 */
#define MAX_NAME_LENGTH 32
#define MAX_VALUE_LENGTH 128

/*
 * HTTP header max values
 */
#define MAX_HEADER_COUNT 64
#define MAX_PARAM_COUNT 64

/*
 * maximum of LEDs
 */
#define MAX_LED_COUNT 32

/*
 * maximal count of paired locomotives
 */
#define MAX_LOCOS 8

/*
 * Webserver
 */
#define HTML_DEFAULT_PAGE "index.html"
 
#endif
