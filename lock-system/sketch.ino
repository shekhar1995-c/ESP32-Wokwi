#include <Keypad.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// Keypad Setup
const int ROW_NUM = 4;
const int COL_NUM = 4;
char keys[ROW_NUM][COL_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte pin_rows[ROW_NUM] = {14, 27, 26, 25};
byte pin_col[COL_NUM] = {33, 32, 3, 1};
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_col, ROW_NUM, COL_NUM);

// Servo Setup
Servo lockServo;
String correctPassword = "1234";  // Correct password to unlock
String enteredPassword = "";  // Store entered password

// OLED Display Setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);  // Initialize serial monitor for debugging

  // Attach servo to pin 10
  lockServo.attach(4);
  lockServo.write(0);  // Initially lock the system

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED display not found"));
    for (;;);  // Halt the program if the OLED display is not connected
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Enter Password:");
  display.display();
}

void loop() {
  char key = keypad.getKey();  // Read key press from the keypad

  if (key) {
    // Append the pressed key to the entered password
    enteredPassword += key;

    // Display the entered password on the OLED screen
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Enter Password:");
    display.setCursor(0, 10);
    display.print(enteredPassword);  // Show entered password on OLED
    display.display();

    // Debugging: Print the entered password to the Serial Monitor
    Serial.print("Entered Password: ");
    Serial.println(enteredPassword);  // Print entered password for debugging

    // If the user presses #, check the entered password
    if (key == '#') {
      if (enteredPassword == correctPassword) {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("Correct Password!");
        display.setCursor(0, 10);
        display.print("Unlocking...");
        display.display();
        unlockMechanism();
      } else {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("Incorrect Password!");
        display.setCursor(0, 10);
        display.print("Try Again.");
        display.display();
      }
      // Clear entered password for next attempt
      enteredPassword = "";
    }
  }
}

void unlockMechanism() {
  // Unlock the lock by moving the servo to 90 degrees
  lockServo.write(90);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Lock Status:");
  display.setCursor(0, 10);
  display.print("Unlocked!");
  display.display();
  delay(3000);  // Keep unlocked for 3 seconds

  // Lock the system again by returning the servo to 0 degrees
  lockServo.write(0);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Lock Status:");
  display.setCursor(0, 10);
  display.print("Locked.");
  display.display();
}
