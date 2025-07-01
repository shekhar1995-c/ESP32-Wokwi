#include "DHT.h"

// Define the DHT sensor type and the pin
#define DHTPIN 15     // GPIO15 is connected to DHT22 data pin
#define DHTTYPE DHT22 // Define the sensor type (DHT22)

DHT dht(DHTPIN, DHTTYPE);  // Initialize the DHT sensor

void setup() {
  // Start the serial communication
  Serial.begin(115200);
  delay(1000);

  // Initialize the DHT sensor
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements
  delay(2000);

  // Read temperature in Celsius and humidity
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if the readings are valid
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    // Print temperature and humidity to the serial monitor
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C\t");
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }
}
