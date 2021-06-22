/*
 * LED class
 * 
 * @autor: Thomas Winkler
 * @copyright: 2019-11-17
 * @lizence: CC0
 */

/*
 * This software is open source under the creative commons CC0 license
 */
 
/*
 * The LED class controlles an output for display.
 * With set_blink a blink style can be added, updated with the blink() method.
 * 
 * blink(int): set the blink time in ms
 * flash_on(): the LED only flashes 10 ms in the speed set by time()
 * flass_off(): normal blinking mode
 */

#ifndef LED_H
#define LED_H

#define RED 0
#define GREEN 1
#define YELLOW 2

#include "config.h"

class LED {

  public:
    LED(int port, int port1=false);
    void blink(int blink_time);
    void flash(int blink_time);
    void invert(bool inverted);
    void on(void);
    void off(void);
    void color(int color);
    void toggle(void);
    void update(void);

  private:
    int _led_port;
    int _led_port1;
    int _led_color;
    bool _inverted;
    double _timeout;
    int _blink_time;
    bool _flash_status;

    void _on(void);
    void _off(void);
    void _flash_on(void);
    void _flash_off(void);
    void _reset(void);
};


#endif
