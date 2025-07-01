// Define the potentiometer and LED pins
#define POT_PIN 34       // Pin connected to the potentiometer (GPIO34)
#define LED_PIN 32       // Pin connected to the LED (GPIO32)

void setup() {
  Serial.begin(115200);  // Start Serial Monitor for debugging
  
  // Set the LED pin as an output
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Read the potentiometer value (0 to 4095 for ESP32)
  int potValue = analogRead(POT_PIN);

  // Print the potentiometer value to Serial Monitor for debugging
  Serial.print("Potentiometer Value: ");
  Serial.println(potValue);

  // Map the potentiometer value (0-4095) to LED brightness (0-255)
  int brightness = map(potValue, 0, 4095, 0, 255);

  // Control the LED brightness using PWM
  analogWrite(LED_PIN, brightness);

  // Delay for a short time to make it readable
  delay(50);
}
