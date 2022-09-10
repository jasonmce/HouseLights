#include "sprites.h"

Sprites::Sprites(uint32_t *color_list, int color_count) {
      colors = color_list;
      num_colors = color_count;
    }

void Sprites::setPalette(uint32_t *color_list, int color_count) {
      colors = color_list;
      num_colors = color_count;
    }

void Sprites::setNumSprites(int num_sprites_to_create) {
  num_sprites = num_sprites_to_create;
}

void Sprites::setup(Adafruit_NeoPixel* strip) {
      int address, start_step;
      int sprite_steps = 15;
      string_length = strip->numPixels();
    
      sprites_list = new CycleSprite*[num_sprites];
     
      for (int sprite_index = 0; sprite_index < num_sprites; sprite_index++) {
        start_step = random(sprite_steps * 2) - 1;
        sprites_list[sprite_index] = new CycleSprite(getRandomAddress(), sprite_steps, colors[sprite_index % num_colors], start_step);
      }       
    }
    
void Sprites::loop(Adafruit_NeoPixel* strip) {
  //  Serial.println("loop_sprites");
    int temp_address = 0;
    
    for (int sprite_index = 0; sprite_index < num_sprites; sprite_index++) {
      sprites_list[sprite_index]->cycle(strip);
      if (sprites_list[sprite_index]->finished()) {
        strip->setPixelColor(sprites_list[sprite_index]->address, 0, 0, 0);
        sprites_list[sprite_index]->setStep(0);
        sprites_list[sprite_index]->setAddress(getRandomAddress());
      }
    }
  }
  
void Sprites::cleanup(Adafruit_NeoPixel* strip) {
  for (int sprite_index = 0; sprite_index < num_sprites; sprite_index++) {
    delete sprites_list[sprite_index];
  }
  delete[] sprites_list;

  string_length = 0;
  num_colors = 0;
  num_sprites = 0;
};


Sprites::~Sprites() {
  for (int sprite_index = 0; sprite_index < num_sprites; sprite_index++) {
    Serial.println("  delete sprite " + String(sprite_index));  
    delete sprites_list[sprite_index];
  }
  delete[] sprites_list;

  string_length = 0;
  num_colors = 0;
  num_sprites = 0;
};
  
