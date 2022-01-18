#include "sprites.h"

Sprites::Sprites(uint32_t *color_list, int color_count) {
      colors = color_list;
      num_colors = color_count;
    }

void Sprites::setPalette(uint32_t *color_list, int color_count) {
      colors = color_list;
      num_colors = color_count;
    }
    
void Sprites::setup(Adafruit_NeoPixel* strip) {
      Serial.println("Num colors is " + String(num_colors));

      int address, start_step, color_step;
      int sprite_steps = 15;
    
      Serial.println("setup_sprites");
     
      for (int sprite_index = 0; sprite_index < NUM_TWINKLERS; sprite_index++) {
        address = (random(STRING_LENGTH / 2) * 2) + 1;  
        start_step = random(sprite_steps * 2) - 1;
        Serial.println("creating index " + String(sprite_index) + " with address " + String(address));  
    
        sprites[sprite_index] = new CycleSprite(address, sprite_steps, colors[sprite_index % num_colors], start_step);
      }       
    }
    
void Sprites::loop(Adafruit_NeoPixel* strip) {
  //  Serial.println("loop_sprites");
    int temp_address = 0;
    for (int sprite_index = 0; sprite_index < NUM_TWINKLERS; sprite_index++) {
      sprites[sprite_index]->cycle(strip);
      if (sprites[sprite_index]->finished()) {
        strip->setPixelColor(sprites[sprite_index]->address, 0, 0, 0);
        temp_address = (random(STRING_LENGTH / 2) * 2) + 1;
        sprites[sprite_index]->setStep(0);
        sprites[sprite_index]->setAddress(temp_address);
        Serial.println("recycling index " + String(sprite_index) + " to address " + String(temp_address));  
      }
    }
  }
  
void Sprites::cleanup(Adafruit_NeoPixel* strip) {};
  
