#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int potPin = 34; // ADC pin for potentiometer
const int centerX = 64;
const int centerY = 56;
const int radius = 40;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED init failed");
    while (true);
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
}

void loop() {
  int potValue = analogRead(potPin);
  int speed = map(potValue, 0, 4095, 0, 120);

  display.clearDisplay();
  drawGauge(speed);
  drawSpeedValue(speed);
  display.display();
  delay(100);
}

void drawGauge(int speed) {
  display.drawCircle(centerX, centerY, radius, WHITE);

  for (int s = 0; s <= 120; s += 20) {
    float angle = radians(map(s, 0, 120, 180, 0));
    int x1 = centerX + cos(angle) * (radius - 5);
    int y1 = centerY - sin(angle) * (radius - 5);
    int x2 = centerX + cos(angle) * radius;
    int y2 = centerY - sin(angle) * radius;
    display.drawLine(x1, y1, x2, y2, WHITE);

    int tx = centerX + cos(angle) * (radius - 12);
    int ty = centerY - sin(angle) * (radius - 12);
    display.setTextSize(1);
    display.setCursor(tx - 6, ty - 4);
    display.print(s);
  }

  // Draw needle
  float needleAngle = radians(map(speed, 0, 120, 180, 0));
  int nx = centerX + cos(needleAngle) * (radius - 10);
  int ny = centerY - sin(needleAngle) * (radius - 10);
  display.drawLine(centerX, centerY, nx, ny, WHITE);

  // Draw center pivot
  display.fillCircle(centerX, centerY, 3, WHITE);
}

void drawSpeedValue(int speed) {
  display.setTextSize(2);
  display.setCursor(40, 0);
  display.print(speed);
  display.print(" km/h");
  Serial.println(speed);

}
