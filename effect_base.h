class EffectBase {

  protected:
//    Adafruit_NeoPixel* _neoPixel;
//    int string_length;
//    uint32_t *colors;
//    int num_colors;

  public:
    /**
     * Store values we will need when displaying this effect.
     */
//    EffectBase(Adafruit_NeoPixel* neoPixel, uint32_t *color_list, int color_count) {
//      _neoPixel = neoPixel;
//      colors = color_list;
//      num_colors = color_count;
//      string_length = _neoPixel->numPixels();
//    }

    virtual void setup(Adafruit_NeoPixel* neoPixel);
    virtual void loop(Adafruit_NeoPixel* neoPixel);
};
