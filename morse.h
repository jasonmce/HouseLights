#include <Adafruit_NeoPixel.h>
#include "effect_base.h"

// Number of cycles to fade up and down.
#define TRANSISTION_STEPS 5
// Number of cycles per beat.  Dot = 1 beat, Dash = 3.
#define BEAT_STEPS 3

char morseF[] = {1,1,3,1, NULL};
char morseC[] = {3,1,3,1, NULL};
char morseK[] = {1,3,1, NULL};
char morseT[] = {3, NULL};
char morseP[] = {1,3,3,1, NULL};
char morseR[] = {3,1,3, NULL};
char morseU[] = {1,1,3, NULL};
char morseS[] = {1,1,1, NULL};
char morseI[] = {1,1, NULL};
char morseA[] = {1,3, NULL};
char morseN[] = {3,1, NULL};
char morseM[] = {3,3, NULL};

char* text[] = {morseF, morseU, morseC, morseK, morseP, morseU, morseT, morseI, morseN};
int text_length = sizeof(text)/sizeof(text[0]);

class MorseLight {
  protected:
    uint32_t color;    
    int letter_index;
    int letter_step;
    int starting_countdown;
    int step_countdown;
    int ending_countdown;
    int break_countdown;
   
  public:
    int address;
    MorseLight(int light_address, int letter_offset, uint32_t my_color) {
      address = light_address;
      color = my_color;
      setLetterIndex(letter_offset);
    }

    void setAddress(unsigned new_address) {
      address = new_address;
    }

    // Advance to this index in the text string.
    void setLetterIndex(int index) {
      setLetterIndexAndStep(index, 0);
    }

    // Advance to this index in the text string.
    void setLetterIndexAndStep(int new_index, int new_step) {
      letter_index = new_index;
      letter_step = new_step;
      starting_countdown = TRANSISTION_STEPS;
      step_countdown = text[letter_index][letter_step] * BEAT_STEPS;
      ending_countdown = TRANSISTION_STEPS;
      break_countdown = BEAT_STEPS * 1; // 1 beats between marks in a letter.
      if (NULL == text[letter_index][letter_step +1]) {
        break_countdown += BEAT_STEPS * 3; // 3 beats at the end of a letter.
      }
    }

    /**
     * Returns color scaled to a brightness of max 255.
     * 
     * @param uint32_t color
     *   32bit color to scale.
     * @param uint8_t brightness
     *   How much to scale it : 0 = black, 255 = full color.
     *   
     * @return uint32_t
     *   The scaled color.
     */
    uint32_t scaleColor(uint32_t color, uint8_t brightness) {
      uint8_t red = (uint8_t)(color >> 16);
      uint8_t green = (uint8_t)(color >>  8);
      uint8_t blue = (uint8_t)color;

      red = (red * brightness) >> 8;
      green = (green * brightness) >> 8;
      blue = (blue * brightness) >> 8;
            
      return ((uint32_t)red << 16) | ((uint32_t)green << 8) | blue;
    }

    uint32_t lightColor() {
      if (starting_countdown > 0) {
        starting_countdown--;
        return scaleColor(color, (255 * (TRANSISTION_STEPS - starting_countdown)) / TRANSISTION_STEPS);
      }
      if (step_countdown > 0) {
        step_countdown--;
        return color;
      }
      if (ending_countdown > 0) {
        ending_countdown--;
        return scaleColor(color, (255 * ending_countdown) / TRANSISTION_STEPS);
      }
      if (break_countdown > 0) {
        break_countdown--;
        return (uint32_t) 0;
      }
      return (uint32_t) 0;
    }

    bool keepGoing() {
      return (starting_countdown > 0) || (step_countdown > 0) || (ending_countdown > 0) || (break_countdown > 0);
    }
   
    void cycle(Adafruit_NeoPixel *strip) {
      strip->setPixelColor(address, lightColor());      

      // If this step is still going, nothing to do.
      if (keepGoing()) {
        return;
      }

      // Move on to the next letter step.
      letter_step++;
      // If we're not at the end of the letter steps, set the countdown and continue.
      if (NULL != text[letter_index][letter_step]) {
        setLetterIndexAndStep(letter_index, letter_step);
        return;
      }
      
      // End of letter processing.
      strip->setPixelColor(address, 0,0,0);        
      // Move to next letter.
      letter_index++;
      // If we're out of letters, that's a sentence!
      if (letter_index < text_length) {
        setLetterIndex(letter_index);
        return;
      }
      // If we're out of letters, that's a sentence!
    }
    
    bool finished() { return (break_countdown <= 0) && letter_index >= text_length; }
};


/**
 * Displays a repeating series of color blocks that appear to rotate along the lights.
 */
class Morse : public EffectBase {
  protected:
    int num_colors = 1;
    uint32_t *colors = NULL;
    int string_length = 0;
    int num_sprites = 0;
    MorseLight **lights_list;
  
  public:

    Morse() {
      num_colors = 0;
    }    
     
    void setPalette(uint32_t *color_list, int color_count) {
      colors = color_list;
      num_colors = color_count;
    }

    // Total number of dots and dashes in our text.
    int totalBeeps() {
      int total_beeps = 0;
      char* letter;
      for (int i = 0; i < text_length; i++) {
        letter = text[i];
        int current_step = 0;        
        do {
          current_step++;
          total_beeps++;
        } while (NULL != letter[current_step]);
      }
      return total_beeps;
    }

    /**
     * Set up the array of 
     */
    void setup(Adafruit_NeoPixel* strip) {
      string_length = strip->numPixels();
      num_sprites = string_length;
      lights_list = new MorseLight*[num_sprites];

      // Each offset is LETTER_INDEX * 10 + step.
      // I don't care enough to write this to alloc text_length * 4 of 2 int arrays.
      int beep_offsets[40];
      char* letter;
      int offset_count = 0;
      for (int letter_index = 0; letter_index < text_length; letter_index++) {
        letter = text[letter_index];
        int current_step = 0;        
        do {
          beep_offsets[offset_count++] = (letter_index * 10) + current_step;
          current_step++;
        } while (NULL != letter[current_step]);
      }

      for (int index = 0; index < string_length; index++) {
        lights_list[index] = new MorseLight(index, 0, colors[index % num_colors]);
        lights_list[index]->setLetterIndexAndStep(
          beep_offsets[index % offset_count] / 10,
          beep_offsets[index % offset_count] % 10       
        );
      }
      strip->show();
    }

    /**
     * Change the lowest light in each band to be its predecessors color.
     * 
     * This creates an "animated progress" effect by only changing one light per band.
     */
    void loop(Adafruit_NeoPixel* strip) {
      for (int index = 0; index < num_sprites; index++) {
        lights_list[index]->cycle(strip);
        if (lights_list[index]->finished()) {
          lights_list[index]->setLetterIndex(0);
        }
      }
    }
    
    void cleanup(Adafruit_NeoPixel* neoPixel) {
      for (int sprite_index = 0; sprite_index < num_sprites; sprite_index++) {
        delete lights_list[sprite_index];
      }
      delete[] lights_list;

      string_length = 0;
      num_colors = 0;
      num_sprites = 0;
    };

    int loopDelay() { return 100; }

    
};
