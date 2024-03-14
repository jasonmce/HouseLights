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

// Use NEO_GBR for the pixel ring to test
Adafruit_NeoPixel strip = Adafruit_NeoPixel(300, 2, NEO_RGB + NEO_KHZ400);

uint32_t BLACK = strip.Color(0, 0, 0);
uint32_t WHITE = strip.Color(255, 255, 255);
uint32_t RED = strip.Color(255, 0, 0);
uint32_t ORANGE = strip.Color(255, 128, 0);
uint32_t YELLOW = strip.Color(255, 225, 0);
uint32_t GREEN = strip.Color(0, 255, 0);
uint32_t BLUE = strip.Color(0, 0, 255);
uint32_t INDIGO = strip.Color(255, 0, 255);
uint32_t VIOLET = strip.Color(128, 0, 255);
uint32_t ROSE = strip.Color(255, 128, 128);
uint32_t GOLD = strip.Color(255, 153, 0051);


EffectBase *current_effect = NULL;
int super_counter = 0;
int loop_counter = 0;
int current_effect_index = 0;

//uint32_t color_palette[7] = {RED, BLUE, ORANGE, INDIGO, YELLOW, ROSE, GREEN};
//uint32_t ukraine_palette[2] = {BLUE, YELLOW};
uint32_t wider_ukraine_palette[6] = {BLUE, BLUE, BLUE, YELLOW, YELLOW, YELLOW};

//uint32_t ukraine_palette[2] = {BLUE, strip.Color(153, 153, 15)};
//
//uint32_t ukraine_usa_palette[24] = {
//  BLUE, strip.Color(153, 153, 15),
//  BLUE, strip.Color(153, 153, 15),
//  BLUE, strip.Color(153, 153, 15),
//  BLUE, strip.Color(153, 153, 15),
//  BLUE, strip.Color(153, 153, 15),
//  BLUE, strip.Color(153, 153, 15),
//  BLUE, strip.Color(153, 153, 15),
//  BLUE, strip.Color(153, 153, 15),
//  RED, RED, RED, WHITE, WHITE, WHITE, BLUE, BLUE   
//};
//
//uint32_t diwali_palette[4] = {
//  GOLD,
//  RED,
//  YELLOW,
//  ORANGE,
//};
//
// uint32_t ukraine_palette_with_spacing[4] = {BLUE, YELLOW, BLACK, BLACK};
//uint32_t voilets_palette[] = {BLUE, INDIGO, VIOLET, ROSE, WHITE};
//uint32_t rouges_palette[] = {RED, INDIGO, VIOLET, ROSE, WHITE};
//uint32_t chinese_palette[] = {RED, GOLD, ORANGE, YELLOW};
// uint32_t chiefs_wide_palette[] = {RED, RED, RED, GOLD, GOLD, GOLD, RED, RED, RED, WHITE, WHITE, WHITE};
// uint32_t chiefs_palette[2] = {RED, GOLD};
//
//uint32_t halloween_palette[4] = {  
//  strip.Color(0, 101, 0), // green
//  strip.Color(31, 0, 67), // purple
//  strip.Color(151, 67, 0), // orange
//  strip.Color(151, 122, 0), // yellow
//};
//// From https://looka.com/blog/12-fall-color-palettes/ &. Pumpkin spice
//uint32_t fall_palette[5] = {  
//  strip.Color(89, 50, 10), // Chocolate brown
//  strip.Color(153, 73, 0), // light brown
//  strip.Color(196, 84, 0), // ochre
//  strip.Color(209, 114, 0), // yellow ochre
//  strip.Color(240, 227, 214), // light pinkish?
//};
//uint32_t pinks_palette[8] = {
//  strip.Color(255, 0, 0),
//  strip.Color(255, 50, 50),
//  strip.Color(255, 100, 100),
//  strip.Color(255, 125, 125),
//  strip.Color(255, 150, 150),
//  strip.Color(255, 200, 200),
//  strip.Color(255, 255, 255),
//  strip.Color(255, 255, 255),
//  };
//uint32_t irish_flag_palette[3] = {
//  strip.Color(22, 155, 98),
//  strip.Color(255, 255, 255),
//  strip.Color(255, 136, 62),
//};
//uint32_t st_pats_palette[] = {
//  GREEN, GREEN, GREEN, GREEN,
//  GOLD, GOLD, GOLD, GOLD, 
//  GREEN, GREEN, GREEN, GREEN,
//  WHITE, WHITE, WHITE, WHITE,
//};

// uint32_t christmas_palette[6] = {
//   RED,
//   GREEN,
//   WHITE,
//   INDIGO,
//   GOLD,
//   VIOLET
// };

// uint32_t blue_and_white[2] = {
//  BLUE,
//  WHITE,
// };

//uint32_t orange_purple[2] = {
//  strip.Color(31, 0, 67), // purple
//  strip.Color(151, 67, 0), // orange
//};

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
  strip.setBrightness(32);
  strip.clear();
  strip.show();
  
//  Sprites* sprites = new Sprites();
//  sprites->setNumSprites(300);
//  sprites->setPalette(ukraine_palette, 2);
//  sprites->anyAddresses();
//  current_effect = sprites;


  Morse* morse = new Morse();
  morse->setPalette(wider_ukraine_palette, sizeof(wider_ukraine_palette) / sizeof(uint32_t));
  current_effect = morse;

//  Patterns::WithSpacing(&strip, color_palette, sizeof(color_palette) / sizeof(uint32_t), 1);
//  ColorParade* colorParade = new ColorParade(blue_and_white, sizeof(blue_and_white) / sizeof(uint32_t), 12);
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
  
  delay(current_effect->loopDelay());

  current_effect->loop(&strip);
  strip.show();
}
