#include <Arduino.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_NeoPixel.h>
#define pin D3
#define num 16
#define DHTTYPE DHT11
#define DHTPIN D4
#define power D2

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(num, pin, NEO_GRB + NEO_KHZ800);

char auth[] = ""; //auth token from blynk
char ssid[] = ""; //your wifi name
char pass[] = ""; //your wifi password
char server[] = "192.168.1.101"; //this time I host a local blynk server, delete if you aren't
int i, r, g, b;
float h, t;
bool l, data;

WidgetLCD lcd(V0);
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t))
  {
    Serial.println("Sensor tidak terdeteksi!");
    return;
  }
  Blynk.virtualWrite(V5, t);
  Blynk.virtualWrite(V6, h);
  lcd.print(0, 0, "Humid :");
  lcd.print(10, 0, h);
  lcd.print(0, 1, "Temp  :");
  lcd.print(10, 1, t);
}

void statis(int r, int g, int b)
{
  for (i = 0; i <= num; i++)
  {
    pixels.setPixelColor(i, pixels.Color(r, g, b));
    pixels.show();
  }
}

void animation1()
{
  for (int i=0; i < num; i++)
  {
    pixels.setPixelColor(i, pixels.Color(21, 0, 4));
    pixels.show();
    delay(50);
  }
  delay(800);
  for (int i = num; i >= 0; i--)    
  {
    pixels.setPixelColor(i, pixels.Color(0, 19, 17));
    pixels.show();
    delay(50);
  }
  delay(800);
  for (int i = 0; i < num; i++)
  {
    pixels.setPixelColor(i, pixels.Color(0, 20, 3));
    pixels.show();
    delay(50);
  }
  delay(800);
  for (int i = num; i >= 0; i--)
    {
    pixels.setPixelColor(i, pixels.Color(12, 13, 0));
    pixels.show();
    delay(50);
     }
  delay(800);
}

BLYNK_WRITE(V1)
{
  r = param[0].asInt();
  g = param[1].asInt();
  b = param[2].asInt();
  statis(r, g, b);
}

BLYNK_WRITE(V2)
{
  l = param.asInt();
  digitalWrite(power, l);
  if (l == 1)
  {
    statis(r, g, b);
  }
  else
  {
    l = 0;
  }
}

BLYNK_WRITE(V3)
{
  data = param.asInt();
  if (data == 0)
  {
    statis(r, g, b);
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
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.clear();
  dht.begin();
  WiFi.begin(ssid, pass);
  Blynk.config(auth, server, 8080);
  Blynk.connect();
  pixels.begin();
  timer.setInterval(1000L, sendSensor);
  pinMode(power, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();
}