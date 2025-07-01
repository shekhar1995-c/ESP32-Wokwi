#include <Adafruit_NeoPixel.h>

#define LED_PIN 5        // Pin connected to the data line of the WS2812B
#define NUM_LEDS 2       // Number of LEDs in the strip

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();         // Initialize the LED strip
  strip.show();          // Turn off all LEDs at the start
}

void loop() {
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  delay(1000);
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  delay(1000);
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
  delay(1000);
}

// Function to fill the strip with one color
void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}
