#include <Adafruit_NeoPixel.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
#include <avr/power.h>
#endif

#include "cycle_sprite.h"
#include "patterns.h"
#include "twinkle.h"

#define STRING_LENGTH 200
#define NUM_TWINKLERS STRING_LENGTH/ 10

CycleSprite *sprites[NUM_TWINKLERS] = { 0 };

Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRING_LENGTH, 2, NEO_RGB + NEO_KHZ400);

uint32_t WHITE = strip.Color(255, 255, 255);
uint32_t BLACK = strip.Color(0, 0, 0);
uint32_t RED = strip.Color(255, 0, 0);
uint32_t ORANGE = strip.Color(255, 128, 0);
uint32_t YELLOW = strip.Color(219, 255, 51);
uint32_t GREEN = strip.Color(0, 255, 0);
uint32_t BLUE = strip.Color(0, 0, 255);
uint32_t INDIGO = strip.Color(128, 0, 255);
uint32_t PURPLE = strip.Color(255, 0, 255);
uint32_t ROSE = strip.Color(255, 150, 150); // Can't say "pink"

uint32_t color_palette[] = {RED, ORANGE, YELLOW, GREEN, BLUE, INDIGO, PURPLE, };

//uint32_t color_palette[] = {WHITE, RED, GREEN, BLUE};
//uint32_t color_palette[] = {
//  strip.Color(255, 0, 255), 
//  strip.Color(242, 194, 85), 
//  strip.Color(97,61,242), 
//  strip.Color(175,242,36),
//  strip.Color(48, 113,242)
//};

/**
 * All pre-loop operations and setup.
 */
void setup() {
  Serial.begin(115200);
  
  strip.begin();
  delay(500);
 
  Patterns::WithSpacing(&strip, color_palette, sizeof(color_palette) / sizeof(uint32_t), 1);
}

/**
 * Working code loop.
 */
void loop() {
  Serial.println("loop");

  delay(500);
  toggleTwinkles(&strip, 10);
}

/**
 * Set up sprites for looping.
 */
void setup_sprites() {
  Serial.println("setup_sprites");

  int sprite_steps = 10;

  for (int sprite_index = 0; sprite_index < NUM_TWINKLERS; sprite_index++) {
    uint16_t address = (uint16_t)(random(0, STRING_LENGTH / 2) * 2 + 1);  
    sprites[sprite_index] = new CycleSprite(&strip, address, WHITE, sprite_steps);
    sprites[sprite_index]->setStep(sprite_index % (sprite_steps * 2));
  }     
}

/**
 * Sprite loop function.
 */
void loop_sprites() {
//  Serial.println("loop_sprites");  
  uint16_t address = 0;
  for (int sprite_index = 0; sprite_index < NUM_TWINKLERS; sprite_index++) {
    sprites[sprite_index]->cycle(&strip);
    if (sprites[sprite_index]->finished()) {
      address = (uint16_t)(random(0, STRING_LENGTH / 2) * 2 + 1);
      sprites[sprite_index]->setStep(0);
      sprites[sprite_index]->setAddress(&strip, (uint16_t)address);
    } else {
      strip.setPixelColor((uint16_t)address, sprites[sprite_index]->use_color);
    }
  }
}
