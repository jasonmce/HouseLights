#ifndef CycleSprite_h
#define CycleSprite_h

#include <Adafruit_NeoPixel.h>

/**
 * Controls operation of a relay.
 */
class CycleSprite {
  protected:
    Adafruit_NeoPixel *strip;
    int address;
    uint32_t start_color;
    uint32_t target_color;
    int steps;
    int total_steps;
    int current_step;

    uint8_t getStepColorByteShift(float percent, int byte_shift);
    uint8_t redStep(float percent);
    uint8_t greenStep(float percent);
    uint8_t blueStep(float percent);
      
  public:
    CycleSprite(Adafruit_NeoPixel *parent_strip, int address, uint32_t color, int steps, int start_step = 0);
    ~CycleSprite();
    void recycle(int index, uint32_t color);    
    uint8_t getRedFromColor(uint32_t c);
    uint8_t getGreenFromColor(uint32_t c);
    uint8_t getBlueFromColor(uint32_t c);
    uint32_t getStepColor(float step_percent);
    void cycle();
    bool finished();

    void debug() { Serial.println("address is " + String(address) + " current step is " + String(current_step) + " of total steps " + total_steps);}
};

#endif
