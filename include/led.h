#ifndef LED_H
#define LED_H
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
// https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-use

#define LED_NUM_LEDS 3

#define LED_1_DEFAULT_RGB 0x00F06000
#define LED_2_DEFAULT_RGB 0x000000FF
#define LED_3_DEFAULT_RGB 0x00FF0000

#define RGB_RED_MASK 0X00FF0000
#define RGB_RED_SHIFT 16

#define RGB_GREEN_MASK 0X0000FF00
#define RGB_GREEN_SHIFT 8

#define RGB_BLUE_MASK 0X000000FF
#define RGB_BLUE_SHIFT 0

void led_write_rgb(uint8_t led, uint32_t rgb);
void led_print_status(void);
void led_setup(void);
void leds_off(void);
void leds_on(void);

#endif
