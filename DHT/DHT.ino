#define BLYNK_TEMPLATE_ID "TMPL3f8WfID7X"
#define BLYNK_TEMPLATE_NAME "DHT"
#define BLYNK_AUTH_TOKEN "u4eaL7kk1ze2Bq-03VsqgIMDt4JZ57TW"

/* Comment this out to disable prints and save space */
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

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void send_data()
{
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0,t);
  Blynk.virtualWrite(V1,h);
  Blynk.virtualWrite(V2,f);
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  dht.begin();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, send_data);
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
