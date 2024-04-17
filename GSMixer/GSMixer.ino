#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#include "FastLED.h"
#include "Sliders.h"
#include "Leds.h"
#include "OLEDs.h"

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_I2C_ADDR)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true)
      ;
  }

  // LEDS Setup
  FastLED.addLeds<WS2812B, PIN_LEDS, GRB>(rgb_led, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS_LEDS);
}

void loop() {
  if (stringComplete) {
    stringComplete = false;
    getCommand();

    if (commandString.equals("SLIDER1")) {
      String text = getTextToPrint();
      oledDisplayCenter(0, text);
    } else if (commandString.equals("SLIDER2")) {
      String text = getTextToPrint();
      oledDisplayCenter(1, text);
    }

    inputString = "";
  }

  sendSliderValues();

  // LEDs müssen vermutlich neu berechnet werden. Wokwi hat es nicht geklappt. Evtl. klappt es mit physischen LEDs
  int sliderval_a = calcSlidersForLEDS(S1, 8, 0);
  int sliderval_b = calcSlidersForLEDS(S2, 8, 11);
  int sliderval_c = calcSlidersForLEDS(S3, 8, 22);
  int sliderval_d = calcSlidersForLEDS(S4, 8, 33);

  // Slider 1
  for (int i = 0; i < sliderval_a; ++i) {
    rgb_led[i] = LED_COLOR_GREEN;
  }

  for (int i = sliderval_a; i < NUM_LEDS; ++i) {
    rgb_led[i] = CRGB::Black;
  }

  // Slider 2
  for (int i = 11; i < sliderval_b; ++i) {
    rgb_led[i] = LED_COLOR_RED;
  }

  for (int i = sliderval_b; i < NUM_LEDS; ++i) {
    rgb_led[i] = CRGB::Black;
  }

  // Slider 3
  for (int i = 22; i < sliderval_c; ++i) {
    rgb_led[i] = LED_COLOR_GREEN;
  }

  for (int i = sliderval_c; i < NUM_LEDS; ++i) {
    rgb_led[i] = CRGB::Black;
  }

  // Slider 4
  for (int i = 33; i < sliderval_d; ++i) {
    rgb_led[i] = LED_COLOR_ORANGE;
  }

  for (int i = sliderval_d; i < NUM_LEDS; ++i) {
    rgb_led[i] = CRGB::Black;
  }

  FastLED.show();
  delay(20);
}
