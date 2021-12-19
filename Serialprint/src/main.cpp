#include <Arduino.h>
#include <head.hpp>

void setup() {
  Serial.begin(115200);
  pinMode(led,OUTPUT);
  pinMode(ledm,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  rafka=not(rafka);
  Serial.println(rafka);
  digitalWrite(led,HIGH);
  digitalWrite(ledm,LOW);
  delay(2000);
  digitalWrite(led,LOW);
  digitalWrite(ledm,HIGH);
  delay(1000);
}