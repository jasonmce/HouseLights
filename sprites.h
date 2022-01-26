#include <Adafruit_NeoPixel.h>

#include "global.h"
#include "effect_base.h"
#include "cycle_sprite.h"


class Sprites : public EffectBase {
  protected:
    CycleSprite **sprites_list;
    int num_sprites;

    int num_colors = 1;
    uint32_t *colors = NULL;


  public:
    Sprites() {
      num_colors = 0;
    }
    Sprites(uint32_t *color_list, int color_count);
    void setNumSprites(int num_sprites_to_create);
    void setPalette(uint32_t *color_list, int color_count);
      
    void setup(Adafruit_NeoPixel* strip);
    void loop(Adafruit_NeoPixel* strip);
    void cleanup(Adafruit_NeoPixel* strip);
};
