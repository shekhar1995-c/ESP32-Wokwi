#include <OneWire.h>                // Library to talk to 1-wire devices like DS18B20
#include <DallasTemperature.h>      // Handles temperature-specific functions
#include <Adafruit_NeoPixel.h>      // Controls the NeoPixel LED ring

#define ONE_WIRE_BUS 4              // DS18B20 connected to GPIO 4
#define NEOPIXEL_PIN 15             // NeoPixel ring data pin
#define NUM_LEDS 16                 // Total LEDs in your NeoPixel ring

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
Adafruit_NeoPixel ring(NUM_LEDS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing Temperature Ring Display...");

  sensors.begin();      // Start temperature sensor
  ring.begin();         // Initialize NeoPixel ring
  ring.show();          // Clear all LEDs

  Serial.println("System Ready. Reading temperature every second...");
  Serial.println("Green = Cool (<26°C), Orange = Warm (26–32°C), Red = Hot (>32°C)");
}

void loop() {
  sensors.requestTemperatures();               // Ask DS18B20 to read temp
  float temp = sensors.getTempCByIndex(0);     // Get the result

  // Display the temp on Serial Monitor
  Serial.print("Current Temperature: ");
  Serial.print(temp);
  Serial.println(" °C");

  // Convert temperature to number of LEDs to light up
  int litLeds = map(temp, 15, 40, 1, NUM_LEDS); // Always lights at least 1 LED
  litLeds = constrain(litLeds, 1, NUM_LEDS);    // Ensures 1 to NUM_LEDS


  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < litLeds) {
      if (temp < 26) {
        ring.setPixelColor(i, ring.Color(0, 150, 0));       // Green for cool
      } else if (temp < 32) {
        ring.setPixelColor(i, ring.Color(255, 165, 0));     // Orange for warm
      } else {
        ring.setPixelColor(i, ring.Color(255, 0, 0));       // Red for hot
      }
    } else {
      ring.setPixelColor(i, 0);   // Turn off remaining LEDs
    }
  }

  ring.show();         // Update the ring with new colors

  delay(1000);         // Wait 1 second
}
