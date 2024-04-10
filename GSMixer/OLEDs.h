// *********** Oleds.h ************* //

// Defines
#define SCREEN_I2C_ADDR 0x3C  // or 0x3C
#define SCREEN_WIDTH 128      // OLED display width, in pixels
#define SCREEN_HEIGHT 64      // OLED display height, in pixels
#define OLED_RST_PIN -1       // Reset pin (-1 if not available)

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
String commandString = "";

// Initial Display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST_PIN);

// Setup Multiplexer
void TCA9548A(uint8_t bus) {
  Wire.beginTransmission(0x70);  //TCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Serial.println("TCA Loop ");
  Serial.println(bus);
  Wire.endTransmission();
}

// Format text and render
void oledDisplayCenter(int Display, String text) {
  int16_t x1;
  int16_t y1;
  uint16_t width;
  uint16_t height;

  display.getTextBounds(text, 0, 0, &x1, &y1, &width, &height);

  // display on horizontal and vertical center
  TCA9548A(Display);
  display.clearDisplay();  // clear display
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor((SCREEN_WIDTH - width) / 2, (SCREEN_HEIGHT - height) / 2);
  display.println(text);  // text to display
  display.display();
}

// Format text from SerialPort (App)
void getCommand() {
  if (inputString.length() > 0) {
    commandString = inputString.substring(1, 8);
  }
}

// Print text
String getTextToPrint() {
  String value = inputString.substring(8, inputString.length() - 2);
  return value;
}

// Listening to incoming data from SerialPort (App)
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}