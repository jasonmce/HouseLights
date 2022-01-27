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


Adafruit_NeoPixel strip = Adafruit_NeoPixel(50, 2, NEO_RGB + NEO_KHZ400);

uint32_t BLACK = strip.Color(0, 0, 0);
uint32_t WHITE = strip.Color(255, 255, 255);
uint32_t RED = strip.Color(255, 0, 0);
uint32_t ORANGE = strip.Color(255, 52, 52);
uint32_t YELLOW = strip.Color(255, 225, 25);
uint32_t GREEN = strip.Color(0, 255, 0);
uint32_t BLUE = strip.Color(0, 0, 255);
uint32_t INDIGO = strip.Color(255, 0, 255);
uint32_t VIOLET = strip.Color(128, 0, 255);
uint32_t ROSE = strip.Color(255, 128, 128);


EffectBase *current_effect = NULL;
int super_counter = 0;
int loop_counter = 0;
int current_effect_index = 0;
uint32_t color_palette[7] = {RED, BLUE, ORANGE, INDIGO, YELLOW, ROSE, GREEN};
uint32_t ukraine_palette[2] = {BLUE, YELLOW};
uint32_t voilets_palette[] = {BLUE, INDIGO, VIOLET, ROSE, WHITE};

/**
 * All pre-loop operations and setup.
 */
void setup() {
  Serial.begin(115200);
  strip.begin();
  delay(500);
  Serial.println("setup()");
  strip.setBrightness(127);
  strip.show();

  strip.fill(BLACK);

  Sprites* sprites = new Sprites();
  sprites->setNumSprites(20);
  sprites->setPalette(voilets_palette, 5);
  sprites->anyAddresses();

//  Patterns::WithSpacing(&strip, color_palette, sizeof(color_palette) / sizeof(uint32_t), 1);
//  ColorParade* colorParade = new ColorParade(color_palette, 2, 16);
  
  current_effect = sprites;
  current_effect->setup(&strip);

  super_counter = 1000;
  loop_counter = 0;
}

/**
 * Working code loop.
 */
void loop() {
  delay(20);
//  Serial.println("loop");
  current_effect->loop(&strip);
  strip.show();

  if (super_counter-- <= 0) {
    super_counter = 1000;
    loop_counter++;
    Serial.println("reset " + String(loop_counter));

    current_effect->cleanup(&strip);
    delete current_effect;

    strip.fill(BLACK);

    Sprites* sprites = new Sprites();
    sprites->setNumSprites(20);
    sprites->setPalette(voilets_palette, 5);
    sprites->anyAddresses();
    current_effect = sprites;
    current_effect->setup(&strip);
  }
}
