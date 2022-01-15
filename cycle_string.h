#ifndef CycleString_h
#define CycleString_h

#include "global.h"
#include "cycle_sprite.h"

class CycleString {

  CycleSprite *sprites[NUM_TWINKLERS] = { 0 };
  int num_lights = 0;

  //CycleSprite* sprites[];// = NULL; // if I was doing malloc
  
  public:
    CycleString(int light_count) {
      num_lights = light_count;
    }

    
    /**
     * Set up sprites for looping, alternating colors from an array.
     */
    void setupSprites(uint8_t *colors[], int num_colors) {
      int address, start_step, color_step;
      int sprite_steps = 25;
    
      Serial.println("setup_sprites");

      //*sprites = (CycleSprite*)malloc(sizeof(CycleSprite*) * num_lights);
     
      for (int sprite_index = 0; sprite_index < num_lights; sprite_index++) {
        address = (random(0, STRING_LENGTH / 2) * 2) + 1;  
        start_step = random(0, (sprite_steps * 2) - 1);
    
        color_step = (sprite_index % num_colors);
        sprites[sprite_index] = new CycleSprite(address, sprite_steps, colors[color_step], start_step);
        sprites[sprite_index]->debug();
      }     
    }

    /**
     * Sprite loop function.
     */
    void loopSprites(Adafruit_NeoPixel &strip) {
    //  Serial.println("loop_sprites");  
      int address = 0;
      for (int sprite_index = 0; sprite_index < NUM_TWINKLERS; sprite_index++) {
        sprites[sprite_index]->cycle(&strip);
        if (sprites[sprite_index]->finished()) {
          strip.setPixelColor(address, 0, 0, 0);
          address = (random(0, STRING_LENGTH / 2) * 2) + 1;
          sprites[sprite_index]->setStep(0);
          sprites[sprite_index]->setAddress(address);
          Serial.println("recycling index " + String(sprite_index) + " to address " + String(address));  
        }
      }
    }
    
  
};

#endif
