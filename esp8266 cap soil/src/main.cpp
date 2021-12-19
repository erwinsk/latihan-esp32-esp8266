#include <Arduino.h>
#define sensorPin A0
float value, humidity;

int convertToPercent(int nilai)
{
  int percentValue = 0;
  percentValue = map(nilai, 594, 200, 0, 100);
  return percentValue;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  value=analogRead(sensorPin);
  humidity = convertToPercent(value);
  Serial.print("kelembaban tanah :");
  Serial.print(humidity);
  Serial.println("%");
  delay(2000);
}