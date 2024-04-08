const int NUM_SLIDERS = 2;
const int analogInputs[NUM_SLIDERS] = {A0,A1};

int analogSliderValues[NUM_SLIDERS];

void setup() { 
  for (int i = 0; i < NUM_SLIDERS; i++) {
    pinMode(analogInputs[i], INPUT);
    
  }

  Serial.begin(9600);
}

void loop() {
  updateSliderValues();
  sendSliderValues(); // Actually send data (all the time)
  // printSliderValues(); // For debug
  delay(30);
}

void updateSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
     analogSliderValues[i] = analogRead(analogInputs[i]);
     analogSliderValues[i] = map(analogSliderValues[i],0,1023,0,100);
  }
}

void sendSliderValues() {
  String builtString = String("");

  for (int i = 0; i < NUM_SLIDERS; i++) {
    builtString += String((int)analogSliderValues[i]);

    if (i < NUM_SLIDERS - 1) {
      builtString += String("|");
    }
  }
  
  Serial.println(builtString);
}

void printSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    String printedString = String("Slider #") + String(i + 1) + String(": ") + String(analogSliderValues[i]) + String(" mV");
    Serial.write(printedString.c_str());

    if (i < NUM_SLIDERS - 1) {
      Serial.write(" | ");
    } else {
      Serial.write("\n");
    }
  }
}