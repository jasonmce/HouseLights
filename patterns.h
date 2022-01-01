
#ifndef Patterns_h
#define Patterns_h

#include <Adafruit_NeoPixel.h>

/**
 * Display simple patterns on a string of neopixels.
 */
class Patterns {

  public:
    static void simplePattern(Adafruit_NeoPixel strip, uint32_t colors[], int num_colors);
    static void WithSpacing(Adafruit_NeoPixel strip, uint32_t colors[], int num_colors, int spacing);
};

#endif // ifndef Patterns_h
