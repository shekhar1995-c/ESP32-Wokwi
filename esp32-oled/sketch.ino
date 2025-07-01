#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define OLED display size
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Define the I2C address of the OLED
#define OLED_ADDR 0x3C

// Create an instance of the display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  
  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("OLED initialization failed"));
    while (true); // Stay in an infinite loop if initialization fails
  }

  // Clear the display
  display.clearDisplay();
  
  // Set text properties
  display.setTextSize(1);      
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  
  // Display a message
  display.println(F("Hello, ESP32!"));
  display.display();  // Update the OLED with the content
}

void loop() {
  // Nothing to loop in this simple example
}
