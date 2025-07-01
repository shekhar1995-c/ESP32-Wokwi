// Define the pins for the HC-SR04
#define TRIG_PIN 23
#define ECHO_PIN 22

void setup() {
  Serial.begin(115200); // Start the serial monitor at 115200 baud rate
  pinMode(TRIG_PIN, OUTPUT); // Set the trigger pin as an output
  pinMode(ECHO_PIN, INPUT);  // Set the echo pin as an input
}

void loop() {
  // Send a pulse to the TRIG pin to trigger the ultrasonic burst
  digitalWrite(TRIG_PIN, LOW); 
  delayMicroseconds(2); 
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10); 
  digitalWrite(TRIG_PIN, LOW);
  
  // Read the duration of the pulse on the ECHO pin
  long duration = pulseIn(ECHO_PIN, HIGH);
  
  // Calculate the distance (duration / 2 because the signal travels to the object and back)
  // The speed of sound is approximately 343 meters per second (0.0343 cm/µs)
  long distance = (duration * 0.0343) / 2;
  
  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  delay(500); // Wait for 0.5 seconds before taking the next measurement
}
