#ifndef CycleSprite_h
#define CycleSprite_h

#include <Adafruit_NeoPixel.h>

/**
 * Controls operation of a relay.
 */
class CycleSprite {
  protected:
    Adafruit_NeoPixel *strip;
    unsigned int address;

    unsigned int steps;
    unsigned int total_steps;
    unsigned int current_step;

    uint8_t CycleSprite::getStepColorByteShift(float percent, int byte_shift);
    uint8_t CycleSprite::redStep(float percent);
    uint8_t CycleSprite::greenStep(float percent);
    uint8_t CycleSprite::blueStep(float percent);
      
  public:
    CycleSprite(Adafruit_NeoPixel *parent_strip, unsigned address, uint32_t color, int steps);

    uint32_t use_color;

    void setStep(int new_step) { current_step = new_step; }
    void setAddress(Adafruit_NeoPixel *parent_strip, unsigned new_address) {
      parent_strip->setPixelColor(address, 0, 0, 0);
      address = new_address;
      }
    uint8_t getRedFromColor(uint32_t c);
    uint8_t getGreenFromColor(uint32_t c);
    uint8_t getBlueFromColor(uint32_t c);
    uint32_t getStepColor(Adafruit_NeoPixel *my_strip, float step_percent);
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
