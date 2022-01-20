#include <SPI.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
#include <avr/power.h>
#endif

#include "patterns.h"


// Back to basics: alternating colors.
void Patterns::simplePattern(Adafruit_NeoPixel *light_strip, uint32_t colors[], int num_colors) {
  int string_length = light_strip->numPixels();

  // Fill the strip with the first color.
  light_strip->fill(colors[0], 0, 0);

  // Iterate through the rest and spread them out.
  for (int color_index = 1; color_index < num_colors; color_index++) {
    for(int address = color_index; address < string_length; address += num_colors) {
      light_strip->setPixelColor(address, colors[color_index]);
    }
  }
  light_strip->show();
}


// Back to basics: alternating through list of colors provided.
// Could this be done with Rainbow() and a lot of loops (length / 4)?
void Patterns::WithSpacing(Adafruit_NeoPixel *light_strip, uint32_t colors[], int num_colors, int spacing) {
  int string_length = light_strip->numPixels();

  // Turn off the light_strip.
  light_strip->fill(light_strip->Color(0, 0, 0), 0, 0);

  // Iterate through the rest and spread them out.
  for (int color_index = 0; color_index < num_colors; color_index++) {
    for(int address = color_index; address < string_length; address += (num_colors * (spacing + 1))) {
      light_strip->setPixelColor(address + color_index, colors[color_index]);
    }
  }

  light_strip->show();
}
