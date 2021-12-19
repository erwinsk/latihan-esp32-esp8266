#include <Arduino.h>
#define red D5
#define green D6
#define redinterval 800
#define greeninterval 500
boolean redstat ;
boolean greenstat ;
unsigned long greentimep = 0;
unsigned long redtimep = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  redstat = LOW;
  greenstat = LOW;
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long redtimen = millis();
  unsigned long greentimen = millis();
  if (redtimen - redtimep >= redinterval){
    if (redstat == LOW){
      redstat = HIGH;
    } else {
      redstat=LOW;
    }
    digitalWrite(red,redstat);
    redtimep = redtimen;
  }
  if (greentimen - greentimep >= greeninterval){
    if (greenstat == LOW){
      greenstat = HIGH;
    } else {
      greenstat = LOW;
    }
  digitalWrite(green, greenstat);
  greentimep = greentimen;
  }
}