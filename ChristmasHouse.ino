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
  strip.fill(BLACK);
//  Patterns::WithSpacing(&strip, color_palette, sizeof(color_palette) / sizeof(uint32_t), 1);
  setup_sprites();
}

/**
 * Working code loop.
 */
void loop() {
  delay(50);
  // toggleTwinkles(&strip, 20);
  loop_sprites();
  strip.show();
}

/**
 * Set up sprites for looping, alternating red, blue, and green colors.
 */
void setup_sprites() {
  int address, start_step, red, green, blue;
  
  Serial.println("setup_sprites");

  int sprite_steps = 25;
  
  for (int sprite_index = 0; sprite_index < NUM_TWINKLERS; sprite_index++) {
    int address = (random(0, STRING_LENGTH / 2) * 2) + 1;  
    int start_step = random(0, (sprite_steps * 2) - 1);

    switch (sprite_index % 3) {
      case 0: red = 255; green = 0; blue = 0; break;
      case 1: red = 0; green = 255; blue = 0; break;
      case 2: red = 0; green = 0; blue = 255; break;
      default:
        Serial.println("Wtf sprite index mod 3 is for " + String(sprite_index));
    }

    sprites[sprite_index] = new CycleSprite(address, sprite_steps, red, green, blue, start_step);
  }     
}

/**
 * Sprite loop function.
 */
void loop_sprites() {
//  Serial.println("loop_sprites");  
  int address = 0;
  for (int sprite_index = 0; sprite_index < NUM_TWINKLERS; sprite_index++) {
    sprites[sprite_index]->cycle(&strip);
    if (sprites[sprite_index]->finished()) {
      address = (random(0, STRING_LENGTH / 2) * 2) + 1;
      sprites[sprite_index]->setStep(0);
      sprites[sprite_index]->setAddress(&strip, address);
      Serial.println("recycling index " + String(sprite_index) + " to address " + String(address));  
    }
  }
}
