#include <SPI.h>

#define STRING_LENGTH 200

#include "cycle_sprite.h"

CycleSprite::CycleSprite(Adafruit_NeoPixel *parent_strip, int index, uint32_t color, int num_steps, int start_step = 0) {
  strip = parent_strip;
  address = index;
  target_color = color;
  start_color = strip->getPixelColor(address);
  // Number of steps to take from start to target colors.
  steps = num_steps;
  // Total number of steps in a cycle is twice one direction.
  total_steps = steps * 2;
  current_step = start_step;
//  Serial.println("Sprite address " + String(address) + " index is " + String(index));
  
}

CycleSprite::~CycleSprite() {
  Serial.println("Deleteing address " + String(address));
  strip->setPixelColor(address, start_color);
}

void CycleSprite::recycle(int index, uint32_t color) {
  if (address > STRING_LENGTH) {
    Serial.println("WTF on address " + String(address));
  }
  if (index > STRING_LENGTH) {
    Serial.println("WTF on index " + String(address));
  }  
  strip->setPixelColor(address, start_color);
  address = index;
  start_color = strip->getPixelColor(address);
  target_color = color;
  current_step = 0;
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
  uint8_t base = start_color >> byte_shift;
  uint8_t target = target_color >> byte_shift;
  int diff = target - base;
  return base + (diff * percent);
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


uint32_t CycleSprite::getStepColor(float step_percent) {
//  Serial.println("Get step color in for " + String(step_percent));

//  int base_red = this->getRedFromColor(start_color);
//  int target_red = this->getRedFromColor(target_color);
//  int red_diff = target_red - base_red;
//  int step_red= base_red + (red_diff * step_percent);
//
//  int base_green = this->getGreenFromColor(start_color);
//  int target_green = this->getGreenFromColor(target_color);
//  int green_diff = target_green - base_green;
//  int step_green= base_green + (green_diff * step_percent);
//
//  int base_blue = this->getBlueFromColor(start_color);
//  int target_blue = this->getBlueFromColor(target_color);
//  int blue_diff = target_blue - base_blue;
//  int step_blue= base_blue + (blue_diff * step_percent);

//  Serial.println("Get step color out for " + String(step_red) + ", " + String(step_green) + ", " + String(step_blue));
//  return strip->Color(step_red, step_green, step_blue);
    return strip->Color(this->redStep(step_percent), this->greenStep(step_percent), this->blueStep(step_percent));
}

void CycleSprite::cycle() {
  if (address > STRING_LENGTH) {
    Serial.println("cycle WTF on address " + String(address));
  }

  
  if (current_step >= total_steps) {
    Serial.println("Sprite address " + String(address) + " is done, no more cycling");
    current_step++;
    return;
  }
  float percent_changed = 0;

  if (current_step < total_steps / 2) {
    percent_changed = float(current_step) / (float(total_steps) / 2);
  }
  if (current_step == total_steps / 2) {
    percent_changed = 1.0;
  }
  if (current_step > total_steps / 2) {
    percent_changed = ((float(total_steps) / 2) - (float(current_step) - (float(total_steps) / 2))) / (float(total_steps) / 2);
  }
//  Serial.println(String(address) + " percent changed is " + String(percent_changed));
  strip->setPixelColor(address, this->getStepColor(percent_changed));
  current_step++;
//  Serial.println("Cycle out");
}

bool CycleSprite::finished() {
  return (current_step >= total_steps);
}
