//// Safely and wastefully large.
//int twinkle[2][50];
//// twinkle_step = -1 is the "initialize" value.
//int twinkle_step = -1;
//
///**
// * Randomly picks 5% of the strip to blink on and off.
// * 
// * Assumes odd lights are available to twinkle.
// */
//void toggleTwinkles(Adafruit_NeoPixel *strip) {
//  int half_string_length = strip->numPixels() / 2;
//  uint32_t color_white = strip->Color(255, 255, 255);
//  uint32_t color_black = strip->Color(0, 0, 0);
//
//
//  if (-1 == twinkle_step) {
//    Serial.println("toggleTwinkles - pre-init");
//    for (int count = 0; count < (half_string_length * 0.5); count++) {
//      twinkle[1][count] = random(0, half_string_length) * 2 + 1;
//      strip->setPixelColor(twinkle[1][count], color_white);
//      twinkle[0][count] = random(0, half_string_length) * 2 + 1;
//      strip->setPixelColor(twinkle[0][count], color_white);
//    }
//    twinkle_step = 0;
//    return;
//  }
//  Serial.print("toggleTwinkles - Set ");
//  Serial.println(twinkle_step);
//
//  Serial.print("Turning on ");
//  
//  for (int count = 0; count < (half_string_length * 0.5); count++) {
//    strip->setPixelColor(twinkle[twinkle_step][count], color_black);
//    twinkle[twinkle_step][count] = random(0, half_string_length) * 2 + 1;
//    strip->setPixelColor(twinkle[twinkle_step][count], color_white);
//    Serial.print(twinkle[twinkle_step][count]);
//    Serial.print(" ");
//  }
//  Serial.println("done ");
//  twinkle_step = (twinkle_step + 1) % 2;
//  strip->show();
//}
