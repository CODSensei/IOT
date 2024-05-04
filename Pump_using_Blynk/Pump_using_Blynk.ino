#define BLYNK_TEMPLATE_ID "TMPL3MKTrsJ-L"
#define BLYNK_TEMPLATE_NAME "Irrigation Pump"
#define BLYNK_AUTH_TOKEN "yfPDA7SdFn995WcCk6Nn2996VeHoFi7K"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "SIGNATURE13S2129";
char pass[] = "1935X9oo";

int Soil_Moisture;
int Pump_Status;
int Pump_pin = 16;

BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  int sm = analogRead(A0);
  Serial.print(Soil_Moisture);
  Serial.println("%");
  Soil_Moisture = map(sm , 0 , 1023 , 100 , 0);
  if (Soil_Moisture < 20){
    digitalWrite(Pump_pin,LOW);
    Pump_Status = 1;
  }
  else if (Soil_Moisture > 50){
    digitalWrite(Pump_pin,HIGH);
    Pump_Status = 0;
  }
  Blynk.virtualWrite(V0,Pump_Status);
  Blynk.virtualWrite(V1,Soil_Moisture);
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(Pump_pin,OUTPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  // Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  // Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}

