#define LED 12

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello, ESP32!");
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH);        //led is high
  delay(1000);                    //delay of 1 second
  digitalWrite(LED, LOW);         //led is low
  delay(1000);                    //delay of 1 second
}
