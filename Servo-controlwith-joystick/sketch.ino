#include <ESP32Servo.h>  // Include the Servo library

// Define pin connections
const int joystickXPin = 34;  // X-axis of the joystick
const int joystickYPin = 35;  // Y-axis of the joystick
const int servoPin = 13;      // Pin where the servo is connected

Servo myServo;  // Create a Servo object

void setup() {
  Serial.begin(115200);      // Start serial communication for debugging
  myServo.attach(servoPin);  // Attach the servo to the pin
}

void loop() {
  // Read the joystick's X and Y values (analog inputs)
  int xValue = analogRead(joystickXPin);
  int yValue = analogRead(joystickYPin);
  
  // Map the joystick values (0-4095) to a servo angle (0-180 degrees)
  int servoXPos = map(xValue, 0, 4095, 0, 180);
  int servoYPos = map(yValue, 0, 4095, 0, 180);
  
  // Print the joystick values and the servo positions for debugging
  Serial.print("X Value: ");
  Serial.print(xValue);
  Serial.print(" | Y Value: ");
  Serial.print(yValue);
  Serial.print(" | Servo X Position: ");
  Serial.print(servoXPos);
  Serial.print(" | Servo Y Position: ");
  Serial.println(servoYPos);
  
  // Control the servo motors using the joystick's values
  myServo.write(servoXPos);  // Move the servo based on X-axis
  delay(15);  // Small delay for smooth movement
}
