/**
 * HouseLights application
 * 
 * Signal pin: Mega = 2, NodeMCU = D4
 */

#include <Adafruit_NeoPixel.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
#include <avr/power.h>
#endif

#include "global.h"
#include "cycle_sprite.h"
#include "sprites.h"
#include "patterns.h"
#include "twinkle.h"
#include "color_parade.h"


Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRING_LENGTH, 2, NEO_RGB + NEO_KHZ400);

uint32_t BLACK = strip.Color(0, 0, 0);
uint32_t WHITE = strip.Color(255, 255, 255);
uint32_t RED = strip.Color(255, 0, 0);
uint32_t GREEN = strip.Color(0, 255, 0);
uint32_t BLUE = strip.Color(0, 0, 255);

uint32_t WHITEISH = strip.Color(128, 128, 128);
uint32_t REDISH = strip.Color(128, 0, 0);
uint32_t ORANGISH = strip.Color(128, 26, 26);
uint32_t YELLOWISH = strip.Color(128, 128, 0);
uint32_t GREENISH = strip.Color(0, 128, 0);
uint32_t BLUEISH = strip.Color(0, 0, 128);
uint32_t INDIGOISH = strip.Color(128, 0, 128);
uint32_t VIOLETISH = strip.Color(64, 0, 128);



EffectBase *current_effect = NULL;
int super_counter = 0;
int current_effect_index = 0;

/**
 * All pre-loop operations and setup.
 */
void setup() {
  Serial.begin(115200);
  strip.begin();
  delay(500);
  Serial.println("setup()");

  Sprites* sprites = new Sprites();
  uint32_t test_colors[4] = {BLUEISH, WHITEISH, INDIGOISH, VIOLETISH};
  sprites->setPalette(test_colors, 4);

//  uint32_t color_palette[4] = {REDISH, VIOLETISH, GREENISH, BLUEISH};
//  Patterns::WithSpacing(&strip, color_palette, sizeof(color_palette) / sizeof(uint32_t), 1);
  strip.fill(WHITE);
  strip.show();
  
  current_effect = sprites;
  current_effect->setup(&strip);
}

/**
 * Working code loop.
 */
void loop() {
  delay(50);
  Serial.println("loop");

  current_effect->loop(&strip);
  strip.show();
}
