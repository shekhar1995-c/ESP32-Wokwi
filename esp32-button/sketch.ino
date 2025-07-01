void setup() {
  pinMode(18, INPUT_PULLUP);            // Configure GPIO 18 as input with pull-up
  Serial.begin(115200);                 // Start Serial Monitor
}

void loop() {
  int buttonState = digitalRead(18);    // Read the button state
  if (buttonState == LOW) {             // Button pressed
    Serial.println("Button Pressed");
  } else {                              // Button not pressed
    Serial.println("Button Released");
  }
  delay(100);                           // Small delay to debounce
}
  