// Pin Definitions
const int buttonPin = 14;  // Button connected to GPIO 14
const int ledPin = 23;     // LED connected to GPIO 23

void setup() {
  // Initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
  
  // Initialize the button pin as an input with an internal pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // Read the state of the button (LOW when pressed, HIGH when not pressed)
  int buttonState = digitalRead(buttonPin);
  
  // If the button is pressed, turn on the LED
  if (buttonState == LOW) {
    digitalWrite(ledPin, HIGH);  // Turn LED on
  } else {
    digitalWrite(ledPin, LOW);   // Turn LED off
  }
  
  // Small delay to avoid bouncing issues
  delay(50);
}
