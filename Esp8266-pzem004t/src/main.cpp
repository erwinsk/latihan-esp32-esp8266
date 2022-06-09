#include <Arduino.h>
#include <PZEM004Tv30.h>
#include <Arduino.h>
#include <PZEM004Tv30.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

PZEM004Tv30 pzem(D7, D8);
char ssid[] = "BBTPPI";
char pass[] = "bbtppisemarang2021";
const char *host = "192.168.12.102";

void setup()
{
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)

  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP : ");
  Serial.println(WiFi.localIP());
}

void loop()
{
    Serial.print("Menyambungkan ke : ");
    Serial.println(host);
   float voltage = pzem.voltage();
   if(voltage != NAN){
       Serial.print("Voltage: ");
       Serial.print(voltage);
       Serial.println("V");
   } else {
       Serial.println("Error reading voltage");
   }

   float current = pzem.current();
   if(current != NAN){
       Serial.print("Current: ");
       Serial.print(current);
       Serial.println("A");
   } else {
       Serial.println("Error reading current");
   }

   float power = pzem.power();
   if(current != NAN){
       Serial.print("Power: ");
       Serial.print(power);
       Serial.println("W");
   } else {
       Serial.println("Error reading power");
   }

   float energy = pzem.energy();
   if(current != NAN){
       Serial.print("Energy: ");
       Serial.print(energy,3);
       Serial.println("kWh");
   } else {
       Serial.println("Error reading energy");
   }

   float frequency = pzem.frequency();
   if(current != NAN){
       Serial.print("Frequency: ");
       Serial.print(frequency, 1);
       Serial.println("Hz");
   } else {
       Serial.println("Error reading frequency");
   }

   float pf = pzem.pf();
   if(current != NAN){
       Serial.print("PF: ");
       Serial.println(pf);
   } else {
       Serial.println("Error reading power factor");
   }

   Serial.println();
     WiFiClient client;
  const int httpPort = 82;
  if (!client .connect(host, httpPort))
  {
    Serial.println("Koneksi gagal...");
    return;
  }
    client .print(String("GET /add.php?")); //jangan lupa ini juga diganti sesuai directory
    client .print("&voltase=");
    client .print(voltage);
    client .print("&arus=");
    client .print(current);
    client .print("&power=");
    client .print(power);
    client .print("&energy=");
    client .print(energy, 3);
    client .print("&pf=");
    client .print(pf);
    client .print("&frekuensi=");
    client .print(frequency, 1);
    client .print(" HTTP/1.1\r\nHost: host\r\nConnection: keep-alive\r\nAccept: */*\r\n\r\n");
    delay(3000);
    while (client.available())
      {
        // read an incoming byte from the server and print it to serial monitor:
        String line = client .readStringUntil('\r');
        Serial.println(line);
      }
    client.stop();
    Serial.println();
    Serial.println("Memutus koneksi...");
   delay(2000);
}