#ifndef EffectBase_h
#define EffectBase_h

#include <Adafruit_NeoPixel.h>

class EffectBase {

  public:
    virtual void setup(Adafruit_NeoPixel* neoPixel);
    virtual void loop(Adafruit_NeoPixel* neoPixel);
    virtual void cleanup(Adafruit_NeoPixel* neoPixel);
};

#endif
