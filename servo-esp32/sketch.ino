#include <ESP32Servo.h>

Servo myServo;               // Create a Servo object

void setup() {
  myServo.attach(13);        // Attach the Servo to GPIO 13
}

void loop() {
  // Sweep the servo from 0 to 180 degrees
  for (int angle = 0; angle <= 180; angle++) {
    myServo.write(angle);   // Move the servo to the given angle
    delay(15);              // Wait for the servo to reach the position
  }
  
  // Sweep the servo from 180 back to 0 degrees
  for (int angle = 180; angle >= 0; angle--) {
    myServo.write(angle);   // Move the servo to the given angle
    delay(15);              // Wait for the servo to reach the position
  }
}

