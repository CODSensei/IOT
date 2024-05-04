#define BLYNK_TEMPLATE_ID "TMPL3ZAVRIAFl"
#define BLYNK_TEMPLATE_NAME "HOME AUTOMATION"
#define BLYNK_AUTH_TOKEN "rLgvoteieHR9NwEK9WVEuZSulTsPgfZy"
#define BLYNK_PRINT Serial

#include <DHT.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "SIGNATURE13S2129";
char pass[] = "1935X9oo";

BlynkTimer timer;
#define DHTPIN 4 // DHT is Connected to GPIO4
#define DHTTYPE DHT11 // DHT11 is Used 
DHT dht(DHTPIN,DHTTYPE); //Activated DHT as dht

void sent_data()
{
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2,f);
  Blynk.virtualWrite(V3,t);
  Blynk.virtualWrite(V4,h);
}

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin V1
BLYNK_WRITE(V0)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable

  // process received value
   if (pinValue == 0)
 {
   digitalWrite(2,HIGH); // OM
 }
 if (pinValue == 1)
 {
   digitalWrite(2,LOW); // Off
 }

}
BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable

  // process received value
   if (pinValue == 0)
 {
   digitalWrite(16,HIGH); // OM
 }
 if (pinValue == 1)
 {
   digitalWrite(16,LOW); // Off
 }

}


void setup()
{
  // Debug console
  pinMode(16,OUTPUT); // Telling the pin to act as output pin
  pinMode(2,OUTPUT);
  Serial.begin(115200);
  dht.begin();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, sent_data);
  // You can also specify server:
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
  timer.run();
}