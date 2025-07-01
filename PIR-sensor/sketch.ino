#define PIR_PIN 13  // PIR sensor output pin
#define LED_PIN 2   // LED pin

void setup() {
  pinMode(PIR_PIN, INPUT);  // Set PIR sensor pin as input
  pinMode(LED_PIN, OUTPUT); // Set LED pin as output
  Serial.begin(115200);     // Initialize serial monitor
  Serial.println("PIR Sensor with ESP32 and LED - Wokwi Simulation");
}

void loop() {
  int pirState = digitalRead(PIR_PIN); // Read PIR sensor state

  if (pirState == HIGH) {
    digitalWrite(LED_PIN, HIGH); // Turn on LED
    Serial.println("Motion detected!");
  } else {
    digitalWrite(LED_PIN, LOW);  // Turn off LED
    Serial.println("No motion.");
  }

  delay(100); // Small delay to avoid rapid state changes
}
