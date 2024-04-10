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

Slider slider[]{ { A0, 20 }, { A1, 20 } };  // verschiedene Faktoren. Array später erweitern auf 4 Slider.

void sendSliderValues() {
  static uint16_t S1_old = slider[0].read();
  static uint16_t S2_old = slider[1].read();

  uint16_t S1 = slider[0].read();
  uint16_t S2 = slider[1].read();
  
  if (S1_old != S1) {
    Serial.println("S1(" + String(S1) + ")");
    S1_old = S1;
  } else if (S2_old != S2) {
    Serial.println("S2(" + String(S2) + ")");
    S2_old = S2;
  }
}
