#include <SPI.h>

#include "cycle_sprite.h"

CycleSprite::CycleSprite(int index, int num_steps, int red, int green, int blue, int start_step = 0) {
  address = index;

  steps = num_steps;
  current_step = start_step;
  // Total number of steps in a cycle is twice one direction.
  total_steps = steps * 2;

  red_target = red;
  green_target = green;
  blue_target = blue;
}

void CycleSprite::cycle(Adafruit_NeoPixel *my_strip) {
  if (current_step > total_steps) {
    Serial.print("Sprite address " + String(address) + " is done, no more cycling");
    return NULL;
  }

  int percent_changed =  (100 * (steps - abs(steps - current_step))) / steps;

  int red_step = (red_target * percent_changed) / 100;
  int green_step = (green_target * percent_changed) / 100;
  int blue_step = (blue_target * percent_changed) / 100;

//  char buffer[100];
//  sprintf(buffer, "step is %d, r=%d, g=%d, b=%d", current_step, red_step, green_step, blue_step);
//  Serial.println(buffer);

  current_step++;
  my_strip->setPixelColor(address, red_step / 2, green_step / 2, blue_step / 2);
}

bool CycleSprite::finished() {
  return (current_step >= total_steps);
}
