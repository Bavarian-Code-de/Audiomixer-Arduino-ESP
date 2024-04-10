// *********** Leds.h ************* //

// Defines
#define NUM_LEDS 80
#define PIN_LEDS 3
#define LED_COLOR_GREEN CRGB::Green
#define LED_COLOR_ORANGE CRGB::Orange
#define LED_COLOR_RED CRGB::Red
#define BRIGHTNESS_LEDS 255  // ValueRange = 0-255

// Setup LED's
CRGB rgb_led[NUM_LEDS];  // color array of the LED RGB strip

// Calculate Sliders to LED's
int calcSlidersForLEDS(float slider, int divided, int pos) {
  if (pos == 0) {
    return (slider / divided);
  } else {
    return (slider / divided) + pos;
  }
}
