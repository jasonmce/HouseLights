#include <Adafruit_NeoPixel.h>

#ifndef CycleSprite_h
#define CycleSprite_h

class CycleSprite;

/**
 * Controls operation of a relay.
 */
class CycleSprite {
  protected:
    int steps;
    int total_steps;
    int current_step;

    uint8_t red_target;
    uint8_t green_target;
    uint8_t blue_target;

  public:
    int address;

    void setMainValues(int index, int num_steps, int start_step);

    CycleSprite(int index, int num_steps, int red, int green, int blue, int start_step = 0);
    CycleSprite(int index, int num_steps, uint32_t color, int start_step = 0);

    void setStep(int new_step) { current_step = new_step; }
    void setAddress(unsigned new_address) {
      address = new_address;
      }
    void cycle(Adafruit_NeoPixel *my_strip);
    bool finished();

    void debug() {
      char buffer[100];
      sprintf(buffer, "address is %u current step is %u of total steps %u",
      address, current_step, total_steps);
      Serial.println(buffer);
    };
  protected:
    // These are from adafruit's neopixel library.
    uint32_t color(uint8_t r, uint8_t g, uint8_t b) {
      return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
    }


};

#endif
