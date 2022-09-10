#include <Adafruit_NeoPixel.h>

#include "effect_base.h"

/**
 * Displays a repeating series of color blocks that appear to rotate along the lights.
 */
class ColorParade : public EffectBase {
  protected:
    int num_colors, width, cycle_length, string_length;
    uint32_t *colors;
    int counter;
  
  public:
    /**
     * Store values we will need when displaying this effect.
     */
    ColorParade(uint32_t *color_list, int color_count, int segment_width) {
      colors = color_list;
      num_colors = color_count;
      width = segment_width;
      cycle_length = width * num_colors;
      counter = 0;
    }

    /**
     * Display colored bands, (width) lights wide, for the length of the string.
     */
    void setup(Adafruit_NeoPixel* neoPixel) {
      string_length = neoPixel->numPixels();

      for (int index = 0; index < string_length; index++) {
        int my_color = (index / width) % num_colors;
        neoPixel->setPixelColor(index, colors[my_color]);
      }
      neoPixel->show();
      
    }

    /**
     * Change the lowest light in each band to be its predecessors color.
     * 
     * This creates an "animated progress" effect by only changing one light per band.
     */
    void loop(Adafruit_NeoPixel* neoPixel) {
      // Loop through the bands.
      for (int i = 0; i < num_colors; i++) {
        // Get the color index of the prior band.
        int prior_color = (num_colors + i - 1) % num_colors;
        // Set the lowest light in each occurance of this band to it's predecessors color.
        for (int j = (i * width + counter) % cycle_length; j < string_length; j += num_colors * width) {
          neoPixel->setPixelColor(j, colors[prior_color]);
        }
      }
      counter = (counter + 1) % cycle_length;
      Serial.print("counter is " + String(counter));
    }
    void cleanup(Adafruit_NeoPixel* neoPixel) {};
    
    int loopDelay() { return 100; }

};
