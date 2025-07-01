#include <Wire.h>
#include <Adafruit_SSD1306.h>

// Define the A4988 driver pins
#define DIR_PIN 32   // Direction pin connected to GPIO32
#define STEP_PIN 33  // Step pin connected to GPIO33

// OLED Display Settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // No reset pin for Wokwi simulation
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Potentiometer Pin
#define POT_PIN 34         // Potentiometer connected to GPIO34

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED display not found"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  // Set the direction and step pins as outputs
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  
  // Initialize display
  display.println("Step Motor Speed Control");
  display.display();
  delay(2000);  // Show the message for 2 seconds
}

void loop() {
  // Read potentiometer value (0 to 1023)
  int potValue = analogRead(POT_PIN);

  // Map the potentiometer value to a range of 1 to 1000 RPM
  int motorSpeed = map(potValue, 0, 1023, 1, 1000);
  
  // Display motor speed on OLED screen
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Speed: ");
  display.print(motorSpeed);
  display.println(" RPM");
  display.display();

  // Rotate the stepper motor based on the potentiometer speed
  // Set direction (CW or CCW)
  digitalWrite(DIR_PIN, HIGH);  // Set the direction to clockwise (change to LOW for counterclockwise)
  
  // Pulse the step pin to move the motor
  digitalWrite(STEP_PIN, HIGH);
  delayMicroseconds(1000000 / motorSpeed);  // Adjust delay to change motor speed
  digitalWrite(STEP_PIN, LOW);
  delayMicroseconds(1000000 / motorSpeed);  // Adjust delay to change motor speed
  
  // Print potentiometer value to Serial Monitor (for debugging)
  Serial.print("Potentiometer Value: ");
  Serial.println(potValue);
}
