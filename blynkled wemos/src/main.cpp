#include <Arduino.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp8266.h>
#include <Adafruit_NeoPixel.h>
#define pin D3
#define num 16

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(num, pin, NEO_GRB + NEO_KHZ800);

char auth[] = ""; //auth token from blynk
char ssid[] = ""; //your wifi name
char pass[] = ""; //your wifi password
int i, r, g, b;

void statis(int r,int g,int b)
{
  for (i = 0; i <= num; i++) 
  {
    pixels.setPixelColor(i, pixels.Color(r,g,b));
    pixels.show();
  }
}

BLYNK_WRITE(V1){
  r = param[0].asInt();
  g = param[1].asInt();
  b = param[2].asInt();
  statis(r, g, b);
}

void setup() {
  // put your setup code here, to run once:
  Blynk.begin(auth, ssid, pass);
  pixels.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
}