
// Back to basics: alternating red, green, blue, white.
void rgbPattern(Adafruit_NeoPixel strip, uint32_t colors[], int num_colors) {
  int string_length = strip.numPixels();

  // Fill the strip with the first color.
  strip.fill(colors[0], 0, 0);

  // Iterate through the rest and spread them out.
  for (int color_index = 1; color_index < num_colors; color_index++) {
    for(int address = color_index; address < string_length; address += num_colors) {
      strip.setPixelColor(address, colors[color_index]);
    }
  }
  strip.show();
}


// Back to basics: alternating through list of colors provided.
// Could this be done with Rainbow() and a lot of loops (length / 4)?
void multicolorFillWithSpacing(Adafruit_NeoPixel strip, uint32_t colors[], int num_colors, int spacing) {
  int string_length = strip.numPixels();

  // Turn off the strip.
  strip.fill(strip.Color(0, 0, 0), 0, 0);

  // Iterate through the rest and spread them out.
  for (int color_index = 0; color_index < num_colors; color_index++) {
    for(int address = color_index; address < string_length; address += (num_colors * (spacing + 1))) {
      strip.setPixelColor(address + color_index, colors[color_index]);
    }
  }

  strip.show();
}
