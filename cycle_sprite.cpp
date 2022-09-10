#include <SPI.h>

#include "cycle_sprite.h"

/**
 * Everything the constructor does except set colors.
 */
void CycleSprite::setMainValues(int index, int num_steps, int start_step) {
  address = index;

  steps = num_steps;
  current_step = start_step;
  // Total number of steps in a cycle is twice one direction.
  total_steps = steps * 2;  
}

/**
 * Constructor using separate RGB values.
 */
CycleSprite::CycleSprite(int index, int num_steps, int red, int green, int blue, int start_step) {
  setMainValues(index, num_steps, start_step);
  red_target = red;
  green_target = green;
  blue_target = blue;
}

/**
 * Constructor using a color element array.
 */
CycleSprite::CycleSprite(int index, int num_steps, uint32_t color, int start_step) {
  setMainValues(index, num_steps, start_step);

  red_target = (uint8_t)(color >> 16);
  green_target = (uint8_t)(color >>  8);
  blue_target = (uint8_t)color;
}


void CycleSprite::cycle(Adafruit_NeoPixel *my_strip) {
  if (current_step > total_steps) {
    return ;
  }

  int percent_changed =  (100 * (steps - abs(steps - current_step))) / steps;

  int red_step = (red_target * percent_changed) / 100;
  int green_step = (green_target * percent_changed) / 100;
  int blue_step = (blue_target * percent_changed) / 100;

  current_step++;
  my_strip->setPixelColor(address, red_step / 2, green_step / 2, blue_step / 2);
}

/**
 * If this sprite has completed a full cycle and is ready for recycling.
 */
bool CycleSprite::finished() {
  return (current_step >= total_steps);
}
