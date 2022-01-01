//#include <SPI.h>
//
//#include "cycle_sprite.h"
//
//CycleSprite::CycleSprite(Adafruit_NeoPixel *parent_strip, unsigned int index, uint32_t color, int num_steps) {
////  Serial.print(" Using address ");
////  Serial.println(index);      
//  
//  address = index;
//  target_color = color;
//  start_color = strip->getPixelColor(address);
//  // Number of steps to take from start to target colors.
//  steps = num_steps;
//  // Total number of steps in a cycle is twice one direction.
//  total_steps = steps * 2;
//  int steps = num_steps;
//  current_step = 0;
//  strip = parent_strip;
////  Serial.print(" Has address ");
////  Serial.println(address);      
//  
//}
//
//// Later use color stuff from https://community.particle.io/t/extracting-rgb-color-value/30170
//
//
//uint8_t CycleSprite::getRedFromColor(uint32_t c) {
//    return c >> 16;
//}
//
//uint8_t CycleSprite::getGreenFromColor(uint32_t c) {
//    return c >> 8;
//}
//
//uint8_t CycleSprite::getBlueFromColor(uint32_t c) {
//    return c;
//}
//
//uint8_t CycleSprite::getStepColorByteShift(float percent, int byte_shift) {
//  uint8_t base = start_color >> byte_shift;
//  uint8_t target = target_color >> byte_shift;
//  int diff = target - base;
//  int change = uint8_t((target - base) * percent);
//  uint8_t to_return = (diff > 0) ? uint8_t(base + change) : uint8_t(base - change);
////  Serial.print("new value is ");
////  Serial.println(to_return);
//  return to_return;
//}
//
//uint8_t CycleSprite::redStep(float percent){
//  return this->getStepColorByteShift(percent, 16);
//}
//uint8_t CycleSprite::greenStep(float percent){
//  return this->getStepColorByteShift(percent, 8);
//}
//uint8_t CycleSprite::blueStep(float percent){
//  return this->getStepColorByteShift(percent, 0);
//}
//
//
//uint32_t CycleSprite::getStepColor(Adafruit_NeoPixel *my_strip, float step_percent) {
////  return start_color;
//  
//  Serial.println("Get step color in for " + String(step_percent));
//
////  int base_red = this->getRedFromColor(start_color);
////  int target_red = this->getRedFromColor(target_color);
////  int red_diff = target_red - base_red;
////  int step_red= base_red + (red_diff * step_percent);
////  int base_green = this->getGreenFromColor(start_color);
////  int target_green = this->getGreenFromColor(target_color);
////  int green_diff = target_green - base_green;
////  int step_green= base_green + (green_diff * step_percent);
////  int base_blue = this->getBlueFromColor(start_color);
////  int target_blue = this->getBlueFromColor(target_color);
////  int blue_diff = target_blue - base_blue;
////  int step_blue= base_blue + (blue_diff * step_percent);
////  Serial.println("Get step color out for " + String(step_red) + ", " + String(step_green) + ", " + String(step_blue));
////  return my_strip->Color(step_red, step_green, step_blue);
//
////  uint8_t red_step = this->redStep(step_percent);
////  uint8_t blue_step = this->blueStep(step_percent);
////  uint8_t green_step = this->greenStep(step_percent);
//  uint8_t step_to_white = (uint8_t)255 * step_percent;
//
//  return my_strip->Color(step_to_white, step_to_white, step_to_white);
//
//
////  return my_strip->Color(this->redStep(step_percent), this->greenStep(step_percent), this->blueStep(step_percent));
////  return my_strip->Color(0,0,0);
//}
//
//void CycleSprite::cycle(Adafruit_NeoPixel *my_strip) {
//  if ((address > 200) || (address < 0)) {
//    Serial.print("WTF-PRE!!! Sprite address ");
//    Serial.println(address);
//    return NULL;
//  }
//  if (current_step > total_steps) {
//    Serial.print("Sprite address ");
//    Serial.print(address);
//    Serial.println(" is done, no more cycling");
//    return NULL;
//  }
////  Serial.println("Sprite " + String(address) + " step is " + String(current_step));
//  
////  float percent_changed = 0.0;
////  if (current_step < total_steps / 2) {
////    percent_changed = float(current_step) / (float(total_steps) / 2);
////  }
////  if (current_step == total_steps / 2) {
////    percent_changed = 1;
////  }
////  if (current_step > total_steps / 2) {
////    percent_changed = ((float(total_steps) / 2) - (float(current_step) - (float(total_steps) / 2))) / (float(total_steps) / 2);
////  }
//
//  float percent_changed = (float)(total_steps - abs(total_steps - current_step)) / (float)total_steps;
//  Serial.println(percent_changed);
//
//  current_step++;
//  use_color = this->getStepColor(my_strip, percent_changed);
////  new_color = my_strip->Color(0,0,0);
////  uint8_t red_step = this->redStep(percent_changed);
////  uint8_t green_step = this->greenStep(percent_changed);
////  uint8_t blue_step = this->blueStep(percent_changed);
////  uint32_t new_color = my_strip->Color(red_step, green_step, blue_step);
////  uint32_t new_color = my_strip->Color(0,0,0);
//
////  char buffer[100];
////  sprintf(buffer," red %u green %u blue %u final %u",
////    red_step, green_step, blue_step, new_color);
////  Serial.println(buffer);
//  
//
////  my_strip->setPixelColor(address, red_step, green_step, blue_step);
//}
//
//bool CycleSprite::finished() {
//  return (current_step >= total_steps);
//}
