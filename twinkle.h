// Safely and wastefully large.
int twinkle[2][50];
// twinkle_step = -1 is the "initialize" value.
int twinkle_step = -1;

/**
 * Randomly picks {percent_lit}% of the strip to blink on and off.
 * 
 * Assumes odd lights are available to twinkle.
 * 
 * @param Adafruit_NeoPixel *lights
 *   Adafruit_NeoPixel pointer for performing light counting and changing.
 * @param int percent_lit
 *   Number between 0-100 to determine how many bulbs to twinkle.
 */
void toggleTwinkles(Adafruit_NeoPixel *lights, int percent_lit) {
  uint32_t color_white = lights->Color(255, 255, 255);
  uint32_t color_black = lights->Color(0, 0, 0);

  int num_lit = (lights->numPixels() * percent_lit) / 100;
  int half_string_length = lights->numPixels() / 2;

  if (-1 == twinkle_step) {
    for (int count = 0; count < num_lit; count++) {
      twinkle[1][count] = random(0, half_string_length) * 2 + 1;
      lights->setPixelColor(twinkle[1][count], color_white);
      twinkle[0][count] = random(0, half_string_length) * 2 + 1;
      lights->setPixelColor(twinkle[0][count], color_white);
    }
    twinkle_step = 0;
    return;
  }

  for (int count = 0; count < num_lit; count++) {
    lights->setPixelColor(twinkle[twinkle_step][count], color_black);
    twinkle[twinkle_step][count] = random(0, half_string_length) * 2 + 1;
    lights->setPixelColor(twinkle[twinkle_step][count], color_white);
  }
  twinkle_step = (twinkle_step + 1) % 2;
  lights->show();
}
