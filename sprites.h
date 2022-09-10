#include <Adafruit_NeoPixel.h>

#include "effect_base.h"
#include "cycle_sprite.h"


class Sprites : public EffectBase {
  protected:
    CycleSprite **sprites_list;
    int num_sprites;

    int num_colors = 1;
    uint32_t *colors = NULL;
    int string_length = 0;
    bool only_odd_addresses = true;


  public:
    Sprites() {
      num_colors = 0;
    }
    ~Sprites();
    Sprites(uint32_t *color_list, int color_count);
    void setNumSprites(int num_sprites_to_create);
    void setPalette(uint32_t *color_list, int color_count);

    void onlyOddAddresses() { only_odd_addresses = true; }
    void anyAddresses() { only_odd_addresses = false; }

    // Returns any address 
    int getRandomAddress() {
      int random_address = random(string_length);
      return only_odd_addresses ? random_address + (random_address % 1) : random_address;
    }
    
    void setup(Adafruit_NeoPixel* strip);
    void loop(Adafruit_NeoPixel* strip);
    void cleanup(Adafruit_NeoPixel* strip);
    int loopDelay() { return 100; }
};
