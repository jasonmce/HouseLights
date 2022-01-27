#include <Adafruit_NeoPixel.h>

#ifndef EffectBase_h
#define EffectBase_h

class EffectBase {

  public:
    virtual void setup(Adafruit_NeoPixel* neoPixel);
    virtual void loop(Adafruit_NeoPixel* neoPixel);
    virtual void cleanup(Adafruit_NeoPixel* neoPixel);
};

#endif
