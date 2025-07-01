#define STEP_PIN 16
#define DIR_PIN 17

const int stepsPerRevolution = 200;

void setup() {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  digitalWrite(DIR_PIN, HIGH);    // Set the initial direction to clockwise
}

void loop() {
  for (int i = 0; i < stepsPerRevolution; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(1000);  // Adjust this to control motor speed
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(1000);
  }

  delay(1000);  // Wait for 1 second before changing direction

  digitalWrite(DIR_PIN, LOW);    // Change direction to counter-clockwise

  for (int i = 0; i < stepsPerRevolution; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(1000);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(1000);
  }

  delay(1000);  // Wait for 1 second before the next loop
  digitalWrite(DIR_PIN, HIGH);
}
