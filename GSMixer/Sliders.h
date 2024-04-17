#include <stdint.h>
// *********** Sliders.h ************* //
class Slider {
  const uint8_t pin;            // analog pin to read
  const uint16_t filterFactor;  // weight of each new value
  float filteredValue = 0;      // current value
  uint16_t count = 0;           // current measurements under filter factors

public:
  Slider(uint8_t pin, uint16_t filterFactor = 100)
    : pin(pin), filterFactor(filterFactor) {}

  // fitered read
  uint16_t read() {
    int adc = analogRead(pin);
    int newValue = map(adc, 0, 1023, 0, 100);
    uint16_t factor = filterFactor;
    if (count < filterFactor) {
      factor = count++;
    }
    filteredValue = ((filteredValue * factor) + newValue) / (factor + 1);
    return round(filteredValue);
  }
};

Slider slider[]{ { A0, 20 }, { A1, 20 }, { A2, 20 }, { A3, 20 } };  // verschiedene Faktoren. Array später erweitern auf 4 Slider.
uint16_t S1;
uint16_t S2;
uint16_t S3;
uint16_t S4;

void sendSliderValues() {
  static uint16_t S1_old = slider[0].read();
  static uint16_t S2_old = slider[1].read();
  static uint16_t S3_old = slider[2].read();
  static uint16_t S4_old = slider[3].read();

  S1 = slider[0].read();
  S2 = slider[1].read();
  S3 = slider[2].read();
  S4 = slider[3].read();
  
  if (S1_old != S1) {
    Serial.println("S1(" + String(S1) + ")");
    S1_old = S1;
  } else if (S2_old != S2) {
    Serial.println("S2(" + String(S2) + ")");
    S2_old = S2;
  } else if (S3_old != S3) {
    Serial.println("S3(" + String(S3) + ")");
    S3_old = S3;
  } else if (S4_old != S4) {
    Serial.println("S4(" + String(S4) + ")");
    S4_old = S4;
  }
}
