#include <Wire.h>              // Include Wire library for I2C communication
#include <LiquidCrystal_I2C.h>  // Include library for LCD
#include <RTClib.h>             // Include the RTC library for DS1307

// Create an object for the DS1307 RTC module
RTC_DS1307 rtc;

// Create an object for the LCD (I2C Address: 0x27, 16x2 LCD)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Initialize Serial Monitor for debugging
  Serial.begin(115200);

  // Initialize the DS1307 RTC module
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);  // Halt if the RTC is not connected
  }

  // Set the RTC time only if the time has not been set before
  // You can uncomment this line to set the time the first time you run the program
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  // Set to the compile time

  // Initialize the LCD and turn on the backlight
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Digital Clock");
}

void loop() {
  // Get the current date and time from the DS1307 RTC
  DateTime now = rtc.now();

  // Display the current time on the LCD
  lcd.setCursor(0, 1);  // Set cursor to the second row
  lcd.print(now.hour(), DEC);   // Display hour
  lcd.print(":");
  lcd.print(now.minute(), DEC); // Display minute
  lcd.print(":");
  lcd.print(now.second(), DEC); // Display second

  delay(1000);  // Update every 1 second
}
