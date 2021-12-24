
#include <Adafruit_NeoPixel.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
#include <avr/power.h>
#endif

#include "cycle_sprite.h"
#include "twinkle.h"
#include "patterns.h"

// There are 11 lights on the strip connected to pin 2.
#define STRING_LENGTH 200
#define NUM_TWINKLERS 9


Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRING_LENGTH, 2, NEO_RGB + NEO_KHZ800);
 
uint32_t WHITE = strip.Color(255, 255, 255);
uint32_t BLACK = strip.Color(0, 0, 0);
uint32_t RED = strip.Color(255, 0, 0);
uint32_t GREEN = strip.Color(0, 255, 0);
uint32_t BLUE = strip.Color(0, 0, 255);
uint32_t PURPLE = strip.Color(255, 0, 255);
uint32_t ROSE = strip.Color(255, 150, 150); // Can't say "pink"
uint32_t YELLOW = strip.Color(219, 255, 51);

uint32_t color_palette[] = {RED, GREEN, PURPLE, YELLOW, ROSE, BLUE};



CycleSprite *sprites[NUM_TWINKLERS] = { 0 };
int sprite_steps = 20;


void setup() {
  Serial.begin(115200);
  
  strip.begin();
  delay(500);
 
  multicolorFillWithSpacing(strip, color_palette, 4, 1);

  int address, start_step;
  
  for (int sprite_index = 0; sprite_index < NUM_TWINKLERS; sprite_index++) {
    address = random(0, STRING_LENGTH / 2) * 2 + 1;
    Serial.println("Address is " + String(address));
    
    start_step = sprite_index % (sprite_steps * 2);
    sprites[sprite_index] = new CycleSprite(&strip, address, WHITE, sprite_steps);
  }    
}


//      delete sprites[sprite_index];
//      sprites[sprite_index] = new CycleSprite(&strip, address, WHITE, sprite_steps);

void loop() {
  int address = 0;

  for (int sprite_index = 0; sprite_index < NUM_TWINKLERS; sprite_index++) {
    if (sprites[sprite_index]->finished()) {
      Serial.println("Recycling " + String(sprite_index));
      address = random(0, STRING_LENGTH / 2) * 2 + 1;
      sprites[sprite_index]->recycle(address, WHITE);
    } else {
      Serial.println("cycling " + String(sprite_index));
      
      sprites[sprite_index]->cycle();
    }
  }
  strip.show();
  delay(25);
}
