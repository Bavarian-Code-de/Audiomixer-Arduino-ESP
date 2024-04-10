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
  // int sliderval_a = calcSlidersForLEDS(slider[0].read(), 50, 0);
  // int sliderval_b = calcSlidersForLEDS(slider[1].read(), 50, 20);
  // int sliderval_c = calcSlidersForLEDS(slider[2].read(), 50, 40);
  // int sliderval_d = calcSlidersForLEDS(slider[3].read(), 50, 60);

  // int sliderval_a = S1;
  // int sliderval_b = S2;

  // // Slider 1
  // for (int i = 0; i < sliderval_a; ++i) {
  //   rgb_led[i] = LED_COLOR_GREEN;
  // }

  // for (int i = sliderval_a; i < NUM_LEDS; ++i) {
  //   rgb_led[i] = CRGB::Black;
  // }

  // // Slider 2
  // for (int i = 20; i < sliderval_b; ++i) {
  //   rgb_led[i] = LED_COLOR_GREEN;
  // }

  // for (int i = sliderval_b; i < NUM_LEDS; ++i) {
  //   rgb_led[i] = CRGB::Black;
  // }

  // // Slider 3
  // for (int i = 40; i < sliderval_c; ++i) {
  //   rgb_led[i] = LED_COLOR_GREEN;
  // }

  // for (int i = sliderval_c; i < NUM_LEDS; ++i) {
  //   rgb_led[i] = CRGB::Black;
  // }

  // // Slider 4
  // for (int i = 60; i < sliderval_d; ++i) {
  //   rgb_led[i] = LED_COLOR_GREEN;
  // }

  // for (int i = sliderval_d; i < NUM_LEDS; ++i) {
  //   rgb_led[i] = CRGB::Black;
  // }

  FastLED.show();
  delay(20);
}
