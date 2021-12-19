#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 12

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensor(&oneWire);
float suhuDS18;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Menginisiasikan setup kecepatan komunikasi
  sensor.begin();      //Menginisiasikan sensor One-Wire DS18B20
  pinMode(ONE_WIRE_BUS, INPUT_PULLUP);
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensor.setResolution(12);
  sensor.requestTemperatures();
  suhuDS18 = sensor.getTempCByIndex(0);
  Serial.println(suhuDS18,4);
  delay(1000);
}