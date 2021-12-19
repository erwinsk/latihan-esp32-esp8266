#include <Arduino.h>
int led = 4;
int task;

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  task = 0;
}
void loop()
{
  task = task + 1;
  digitalWrite(led, HIGH);
  delay(10000);
  digitalWrite(led, LOW);
  delay(2000);
  Serial.print("Task");
  Serial.println(task);
}