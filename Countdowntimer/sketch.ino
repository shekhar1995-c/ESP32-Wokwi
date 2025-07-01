// ESP32 Countdown Timer with TM1637 4-Digit Display (4 wires)
#define CLK 22          // Clock pin for TM1637
#define DIO 23          // Data pin for TM1637
#define BUTTON_START_PAUSE 26 // Start/Pause button
#define BUTTON_RESET 27      // Reset button

// TM1637 commands and digits (simplified for Wokwi)
const uint8_t SEGMENTS[] = {
  0x3F, // 0
  0x06, // 1
  0x5B, // 2
  0x4F, // 3
  0x66, // 4
  0x6D, // 5
  0x7D, // 6
  0x07, // 7
  0x7F, // 8
  0x6F  // 9
};

int timerValue = 6000; // 60.00 seconds (in hundredths)
bool isRunning = false;
unsigned long lastUpdate = 0;
const int updateInterval = 10; // Update every 10ms

void setup() {
  pinMode(CLK, OUTPUT);
  pinMode(DIO, OUTPUT);
  pinMode(BUTTON_START_PAUSE, INPUT_PULLUP);
  pinMode(BUTTON_RESET, INPUT_PULLUP);
  
  // Initialize TM1637 (basic setup)
  digitalWrite(CLK, HIGH);
  digitalWrite(DIO, HIGH);
  delayMicroseconds(10);
  tm1637Start();
  tm1637Write(0x8F); // Set brightness (0x88-0x8F range)
  tm1637Stop();
}

void loop() {
  // Button handling
  if (digitalRead(BUTTON_START_PAUSE) == LOW) {
    delay(50); // Debounce
    if (digitalRead(BUTTON_START_PAUSE) == LOW) {
      isRunning = !isRunning;
      while (digitalRead(BUTTON_START_PAUSE) == LOW);
    }
  }
  if (digitalRead(BUTTON_RESET) == LOW) {
    delay(50); // Debounce
    if (digitalRead(BUTTON_RESET) == LOW) {
      timerValue = 6000;
      isRunning = false;
      while (digitalRead(BUTTON_RESET) == LOW);
    }
  }

  // Update timer
  if (isRunning && millis() - lastUpdate >= updateInterval) {
    if (timerValue > 0) {
      timerValue--;
    }
    lastUpdate = millis();
  }

  // Display the time
  displayTime(timerValue);
}

// TM1637 low-level functions (simplified for Wokwi)
void tm1637Start() {
  digitalWrite(DIO, HIGH);
  digitalWrite(CLK, HIGH);
  delayMicroseconds(2);
  digitalWrite(DIO, LOW);
  delayMicroseconds(2);
}

void tm1637Stop() {
  digitalWrite(CLK, LOW);
  delayMicroseconds(2);
  digitalWrite(DIO, LOW);
  delayMicroseconds(2);
  digitalWrite(CLK, HIGH);
  delayMicroseconds(2);
  digitalWrite(DIO, HIGH);
}

void tm1637Write(uint8_t data) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(CLK, LOW);
    digitalWrite(DIO, (data >> i) & 1);
    delayMicroseconds(2);
    digitalWrite(CLK, HIGH);
    delayMicroseconds(2);
  }
  // ACK
  digitalWrite(CLK, LOW);
  pinMode(DIO, INPUT);
  delayMicroseconds(5);
  pinMode(DIO, OUTPUT);
  digitalWrite(CLK, HIGH);
}

void displayTime(int time) {
  int minutes = time / 100; // e.g., 6000 -> 60
  int seconds = time % 100; // e.g., 6000 -> 00
  uint8_t displayData[4];
  
  displayData[0] = SEGMENTS[minutes / 10]; // Tens of minutes
  displayData[1] = SEGMENTS[minutes % 10] | 0x80; // Ones of minutes + colon (bit 7)
  displayData[2] = SEGMENTS[seconds / 10]; // Tens of seconds
  displayData[3] = SEGMENTS[seconds % 10]; // Ones of seconds

  tm1637Start();
  tm1637Write(0x40); // Command to set data write mode
  tm1637Stop();
  
  tm1637Start();
  tm1637Write(0xC0); // Address of first digit
  for (int i = 0; i < 4; i++) {
    tm1637Write(displayData[i]);
  }
  tm1637Stop();
}