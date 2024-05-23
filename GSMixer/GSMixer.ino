#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#include "Adafruit_EEPROM_I2C.h"
#include "Adafruit_FRAM_I2C.h"
#include "FastLED.h"
#include "Sliders.h"
#include "Leds.h"
#include "OLEDs.h"

Adafruit_FRAM_I2C i2ceeprom;

unsigned long previousMillis = millis();

String Display1 = "OLED 1"; // Fiktiver Wert für Testzwecke
String saved;

#define EEPROM_ADDR 0x50  // the default address!

void setup() {
  Serial.begin(9600);
  Wire.begin();

  uint16_t num;

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_I2C_ADDR)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  if (i2ceeprom.begin(0x50)) {  // you can stick the new i2c addr in here, e.g. begin(0x51);
    Serial.println("Found I2C EEPROM");
  } else {
    Serial.println("I2C EEPROM not identified ... check your connections?\r\n");
    while (1) delay(10);
  }

  // LEDS Setup
  FastLED.addLeds<WS2812B, PIN_LEDS, GRB>(rgb_led, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS_LEDS);

  // num = i2ceeprom.writeObject(0x00, Display1); // String wird in FRAM gespeichert -> sollte nur einmal verwendet werden beim Hochladen des sketches, dann auskommentiert werden
  i2ceeprom.readObject(0x00, saved); // Zuvor gespeicherter String wird aus FRAM gelesen
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

  oledDisplayCenter(0, saved);

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 20) {
    previousMillis = currentMillis;
    sendSliderValues();
  }

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
}
