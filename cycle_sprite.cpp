#include <SPI.h>

#include "cycle_sprite.h"

CycleSprite::CycleSprite(Adafruit_NeoPixel *parent_strip, unsigned int index, uint32_t color, int num_steps) {
//  Serial.print(" Using address ");
//  Serial.println(index);      
  
  address = index;
  // Number of steps to take from start to target colors.
  steps = num_steps;
  // Total number of steps in a cycle is twice one direction.
  total_steps = steps * 2;
  int steps = num_steps;
  current_step = 0;
  strip = parent_strip;
//  Serial.print(" Has address ");
//  Serial.println(address);      
  
}

// Later use color stuff from https://community.particle.io/t/extracting-rgb-color-value/30170


uint8_t CycleSprite::getRedFromColor(uint32_t c) {
    return c >> 16;
}

uint8_t CycleSprite::getGreenFromColor(uint32_t c) {
    return c >> 8;
}

uint8_t CycleSprite::getBlueFromColor(uint32_t c) {
    return c;
}

uint8_t CycleSprite::getStepColorByteShift(float percent, int byte_shift) {
  return (uint8_t)(255 * percent);
}

uint8_t CycleSprite::redStep(float percent){
  return this->getStepColorByteShift(percent, 16);
}
uint8_t CycleSprite::greenStep(float percent){
  return this->getStepColorByteShift(percent, 8);
}
uint8_t CycleSprite::blueStep(float percent){
  return this->getStepColorByteShift(percent, 0);
}


uint32_t CycleSprite::getStepColor(Adafruit_NeoPixel *my_strip, float step_percent) {
  return 1;
}

void CycleSprite::cycle(Adafruit_NeoPixel *my_strip) {
  if ((address > 200) || (address < 0)) {
    Serial.print("WTF-PRE!!! Sprite address ");
    Serial.println(address);
    return NULL;
  }
  if (current_step > total_steps) {
    Serial.print("Sprite address ");
    Serial.print(address);
    Serial.println(" is done, no more cycling");
    return NULL;
  }


  float percent_changed = (float)(abs(steps - current_step)) / (float)steps;
  Serial.println(percent_changed);

  current_step++;
  use_color = this->getStepColor(my_strip, percent_changed);


//  my_strip->setPixelColor(address, red_step, green_step, blue_step);
}

bool CycleSprite::finished() {
  return (current_step >= total_steps);
}
