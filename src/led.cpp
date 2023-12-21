#include <led.h>
#include "pins.h"

Adafruit_NeoPixel strip(LED_NUM_LEDS, LED_DATA_PIN, NEO_GRB + NEO_KHZ800);



struct led
{
    uint32_t rgb;
};

struct led leds[LED_NUM_LEDS] = {
    {0},
    {LED_2_DEFAULT_RGB},
    {0}};

void led_print_status()
{
    uint32_t rgb;
    uint8_t r, g, b;

    for (uint8_t i = 0; i < LED_NUM_LEDS; i++)
    {
        rgb = strip.getPixelColor(i);
        r = (uint8_t)((rgb & RGB_RED_MASK) >> RGB_RED_SHIFT);
        g = (uint8_t)((rgb & RGB_GREEN_MASK) >> RGB_GREEN_SHIFT);
        b = (uint8_t)((rgb & RGB_BLUE_MASK) >> RGB_BLUE_SHIFT);
        Serial.printf("LED%d R: %d G: %d B: %d\n", i, r, g, b);
    }
}

void led_setup(void)
{
    strip.begin();
    strip.show();
}

void leds_on(void)
{
    for (uint8_t i = 0; i < LED_NUM_LEDS; i++)
    {
        led_write_rgb(i, leds[i].rgb);
    }
}

void leds_off(void)
{

    for (uint8_t i = 0; i < LED_NUM_LEDS; i++)
    {
        strip.setPixelColor(i, 0, 0, 0);
        
    }
    strip.show();
}

void led_write_rgb(uint8_t led, uint32_t rgb)
{
    if (led > LED_NUM_LEDS - 1)
    {
        Serial.println("Invalid LED");
        return;
    }

    leds[led].rgb = rgb;

    uint8_t red = (uint8_t)((rgb & RGB_RED_MASK) >> RGB_RED_SHIFT);
    uint8_t green = (uint8_t)((rgb & RGB_GREEN_MASK) >> RGB_GREEN_SHIFT);
    uint8_t blue = (uint8_t)((rgb & RGB_BLUE_MASK) >> RGB_BLUE_SHIFT);

    //Serial.printf("LED %d %d %d %d\n", led, red, green, blue);
    strip.setPixelColor(led, red, green, blue);
    strip.show();
}
