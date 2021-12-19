#include <Arduino.h>
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = ""; //auth token from blynk
char ssid[] = ""; //your wifi name
char pass[] = ""; //your wifi password
int sensorPin = 34;
int sensorValue = 0;
int humidity = 0;

int convertToPercent(int value)
{
  int percentValue = 0;
  percentValue = map(value, 4095, 1200, 0, 100);
  return percentValue;
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}
void loop()
{
  Blynk.run();
  sensorValue = analogRead(sensorPin);
  humidity = convertToPercent(sensorValue);
  Serial.print("Nilai Sensor : ");
  Serial.println(sensorValue);
  Serial.print("Kelembaban: ");
  Serial.print(humidity);
  Serial.println("%");
  Serial.println(" ");
  delay(1000);
  Blynk.virtualWrite(V2, humidity);
}
