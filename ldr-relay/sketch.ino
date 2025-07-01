#define LDR_PIN 34   // LDR sensor connected to GPIO34
#define RELAY_PIN 12 // Relay connected to GPIO16

int lightLevel = 0;  // Variable to store the light level (0-1023)
int threshold = 500; // Define the threshold for turning the light on/off

void setup() {
  Serial.begin(115200);   // Start Serial Monitor
  pinMode(LDR_PIN, INPUT); // Set LDR pin as input
  pinMode(RELAY_PIN, OUTPUT); // Set Relay pin as output
  Serial.println("Automatic Street Light System");
}

void loop() {
  lightLevel = analogRead(LDR_PIN); // Read the light level

  // Print light level to the Serial Monitor
  Serial.print("Light Level: ");
  Serial.println(lightLevel);

  // Check if it's night time (light level below threshold)
  if (lightLevel < threshold) {
    digitalWrite(RELAY_PIN, HIGH); // Turn on the light (Relay)
    Serial.println("It's dark! Turning on the light...");
  } else {
    digitalWrite(RELAY_PIN, LOW); // Turn off the light (Relay)
    Serial.println("It's bright! Turning off the light...");
  }

  delay(1000);  // Wait for 1 second before reading again
}
