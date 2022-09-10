/**
 * HouseLights application
 * 
 * Runs a set of patterns on a string of WS2811 lights.
 * 
 * Slowly evolving to where a rotation of effects can be specified.
 * 
 * Signal pin: Mega = 2, NodeMCU = D4
 */

#include <Adafruit_NeoPixel.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
#include <avr/power.h>
#endif

#include "cycle_sprite.h"
#include "sprites.h"
#include "patterns.h"
#include "color_parade.h"
#include "morse.h"
#include "ntp.h"


Adafruit_NeoPixel strip = Adafruit_NeoPixel(400, 2, NEO_RGB + NEO_KHZ400);

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
uint32_t GOLD = strip.Color(255, 215, 00);


EffectBase *current_effect = NULL;
int super_counter = 0;
int loop_counter = 0;
int current_effect_index = 0;
uint32_t color_palette[7] = {RED, BLUE, ORANGE, INDIGO, YELLOW, ROSE, GREEN};
uint32_t ukraine_palette[2] = {BLUE, YELLOW};
uint32_t ukraine_palette_with_spacing[4] = {BLUE, YELLOW, BLACK, BLACK};
uint32_t voilets_palette[] = {BLUE, INDIGO, VIOLET, ROSE, WHITE};
uint32_t rouges_palette[] = {RED, INDIGO, VIOLET, ROSE, WHITE};
uint32_t chinese_palette[4] = {RED, GOLD, WHITE, BLACK};
uint32_t pinks_palette[8] = {
  strip.Color(255, 0, 0),
  strip.Color(255, 50, 50),
  strip.Color(255, 100, 100),
  strip.Color(255, 125, 125),
  strip.Color(255, 150, 150),
  strip.Color(255, 200, 200),
  strip.Color(255, 255, 255),
  strip.Color(255, 255, 255),
  };
uint32_t irish_flag_palette[3] = {
  strip.Color(22, 155, 98),
  strip.Color(255, 255, 255),
  strip.Color(255, 136, 62),
};

// Start at zero so it first runs at boot.
int duskCheckCountdown = 0;

/**
 * All pre-loop operations and setup.
 */
void setup() {
  Serial.begin(115200);

  ntp_setup();
  
  strip.begin();
  delay(500);
  Serial.println("setup()");
  strip.setBrightness(127);
  strip.show();

  strip.fill(BLACK);

//  Sprites* sprites = new Sprites();
//  sprites->setNumSprites(300);
//  sprites->setPalette(ukraine_palette, 2);
//  sprites->anyAddresses();
//  current_effect = sprites;


  Morse* morse = new Morse();
  morse->setPalette(ukraine_palette, 2);
  current_effect = morse;


//  Patterns::WithSpacing(&strip, color_palette, sizeof(color_palette) / sizeof(uint32_t), 1);

//  ColorParade* colorParade = new ColorParade(ukraine_palette_with_spacing, 4, 16);
//  current_effect = colorParade;

  current_effect->setup(&strip);

}

/**
 * Working code loop.
 */
void loop() {
//  ntp_loop();
  if (duskCheckCountdown-- < 0) {
    int sleepMinutes = minutesToSleepUntilDark();
    if (0 == sleepMinutes) {
      Serial.printf("It's dark, no sleeping yet");
    }    
    if (0 != sleepMinutes) {
      Serial.printf("Sleep for %d minutes\n", sleepMinutes);
      strip.fill(BLACK);
      strip.show();
      delay(60000);
      return;
    }
    duskCheckCountdown = 300;
  }
  
//  delay(100);
  delay(500);
  Serial.println("loop");
  current_effect->loop(&strip);
  strip.show();
}
