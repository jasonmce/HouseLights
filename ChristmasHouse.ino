/**
 * HouseLights application
 * 
 * Signal pin: Mega = 2, NodeMCU = D4
 */

#include <Adafruit_NeoPixel.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
#include <avr/power.h>
#endif

#include "cycle_sprite.h"
#include "patterns.h"
#include "twinkle.h"
#include "global.h"
#include "color_parade.h"
#include "sprites.h"

//CycleSprite *sprites[NUM_TWINKLERS] = { 0 };

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


uint8_t white[] = {255, 255, 255};
uint8_t black[] = {0, 0, 0};
uint8_t red[] = {255, 0, 0};
uint8_t orange[] = {255, 128, 0};
uint8_t yellow[] = {219, 255, 51};
uint8_t green[] = {0, 255, 0};
uint8_t blue[] = {0, 0, 255};
uint8_t indigo[] = {128, 0, 255};
uint8_t purple[] = {255, 0, 255};
uint8_t rose[] = {255, 150, 150}; // Can't say "pink"

//char colorskis[3] = {0,0,0};
//colorskis = CycleSprite::color_array(RED);
//Serial.println("Colors red:" + String(colorskis[0]) + "G:" + String(colorskis[1]) + "B:" + String(colorskis[2]));


uint32_t these_colors[] = {REDISH, INDIGOISH, VIOLETISH};

Sprites bozos[1] = {Sprites(these_colors, 3)};


uint32_t test_colors_one[4] = {BLUEISH, WHITEISH, INDIGOISH, VIOLETISH};
uint32_t test_colors_two[2] = {REDISH, BLUEISH};


ColorParade colorParade[2] = {
  ColorParade(test_colors_one, 4, 6),
  ColorParade(test_colors_two, 2, 2)
};
//colorParade[0] = ColorParade(test_colors_one, 4, 6, 100);
//colorParade[1] = ColorParade(test_colors_two, 2, 6, 100);

EffectBase *something = NULL;

int super_counter = 0;
int current_effect_index = 0;

/**
 * All pre-loop operations and setup.
 */
void setup() {
  Serial.begin(115200);
  
  strip.begin();
  delay(500);
  strip.fill(WHITEISH);
//  something = &colorParade[current_effect_index];
  something = &bozos[0];
  something->setup(&strip);
}

/**
 * Working code loop.
 */
void loop() {
  delay(50);

  something->loop(&strip);

  
  strip.show();
}

/**
 * Set up sprites for looping, alternating colors from an array.
 */
//void setup_sprites(uint8_t *colors[], int num_colors) {
//  int address, start_step, color_step;
//  int sprite_steps = 25;
//
//  Serial.println("setup_sprites");
// 
//  for (int sprite_index = 0; sprite_index < NUM_TWINKLERS; sprite_index++) {
//    address = (random(STRING_LENGTH / 2) * 2) + 1;  
//    start_step = random(sprite_steps * 2) - 1;
//    Serial.println("creating index " + String(sprite_index) + " with address " + String(address));  
//
//    color_step = (sprite_index % num_colors);
//    sprites[sprite_index] = new CycleSprite(address, sprite_steps, colors[color_step], start_step);
//  }     
//}

/**
 * Sprite loop function.
 */
//void loop_sprites() {
////  Serial.println("loop_sprites");
//  int temp_address = 0;
//  for (int sprite_index = 0; sprite_index < NUM_TWINKLERS; sprite_index++) {
//    sprites[sprite_index]->cycle(&strip);
//    if (sprites[sprite_index]->finished()) {
//      strip.setPixelColor(sprites[sprite_index]->address, 0, 0, 0);
//      temp_address = (random(STRING_LENGTH / 2) * 2) + 1;
//      sprites[sprite_index]->setStep(0);
//      sprites[sprite_index]->setAddress(temp_address);
//      Serial.println("recycling index " + String(sprite_index) + " to address " + String(temp_address));  
//    }
//  }
//}



// untested
void setup_spaced_rainbow_with_twinkles_using_sprites() {
  uint32_t color_palette[4] = {RED, WHITE, GREEN, BLUE};
  Patterns::WithSpacing(&strip, color_palette, sizeof(color_palette) / sizeof(uint32_t), 1);
//  uint8_t *colors[] = {blue, indigo, purple, red, green, rose};
//  setup_sprites(colors, 6);  
}
void loop_spaced_rainbow_with_twinkles_using_sprites() {
//  loop_sprites();
  strip.show();
}

// untested
void setup_white_with_twinkles_using_sprites() {
  strip.fill(WHITE);
//  uint8_t *colors[] = {red, orange, yellow, green, blue, indigo, purple};
//  setup_sprites(colors, 7);
}
void loop_white_with_twinkles_using_sprites() {
//  loop_sprites();
  strip.show();
}
