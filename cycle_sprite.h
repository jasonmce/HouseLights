#ifndef CycleSprite_h
#define CycleSprite_h

#include <Adafruit_NeoPixel.h>

/**
 * Controls operation of a relay.
 */
class CycleSprite {
  protected:
    int address;

    int steps;
    int total_steps;
    int current_step;

    uint8_t red_target;
    uint8_t green_target;
    uint8_t blue_target;

      
  public:
    CycleSprite(int index, int num_steps, int red, int green, int blue, int start_step = 0);

    void setStep(int new_step) { current_step = new_step; }
    void setAddress(Adafruit_NeoPixel *parent_strip, unsigned new_address) {
      parent_strip->setPixelColor(address, 0, 0, 0);
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

      
};

#endif
