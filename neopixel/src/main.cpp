#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_NeoPixel.h>
#define PIN 33
#define NUM 16

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM, PIN, NEO_GRB + NEO_KHZ800);

char auth[] = "f2QvOtzhPKU2rA8Q2XdXzGUsPRHj0qQw";
char ssid[] = "Sawojajar";
char pass[] = "Nokia3315";
int r, g, b, data;

void static1(int r, int g, int b)
{
  for (int i = 0; i <= NUM; i++)
  {
    pixels.setPixelColor(i, pixels.Color(r, g, b));
    pixels.show();
  }
}

void animation1()
{
  for (int i=0; i < NUM; i++)
  {
    pixels.setPixelColor(i, pixels.Color(21, 0, 4));
    pixels.show();
    delay(50);
  }
  delay(800);
  for (int i = NUM; i >= 0; i--)    
  {
    pixels.setPixelColor(i, pixels.Color(0, 19, 17));
    pixels.show();
    delay(50);
  }
  delay(800);
  for (int i = 0; i < NUM; i++)
  {
    pixels.setPixelColor(i, pixels.Color(0, 20, 3));
    pixels.show();
    delay(50);
  }
  delay(800);
  for (int i = NUM; i >= 0; i--)
    {
    pixels.setPixelColor(i, pixels.Color(12, 13, 0));
    pixels.show();
    delay(50);
     }
  delay(800);
}

BLYNK_WRITE(V2)
{
  r = param[0].asInt();
  g = param[1].asInt();
  b = param[2].asInt();
  if (data == 0)
    static1(r, g, b);
}

BLYNK_WRITE(V3)
{
  data = param.asInt();
  if (data == 0)
  {
    static1(r, g, b);
  }
  else if (data == 1)
  {
    for (int i = 0; i <=2; i++)
    {
      animation1();
    }
  }
}

void setup()
{
  Blynk.begin(auth, ssid, pass);
  pixels.begin();
}
void loop()
{
  Blynk.run();
}