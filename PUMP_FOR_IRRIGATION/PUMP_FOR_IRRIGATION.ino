

#include <ESP8266WiFi.h>
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros




char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

int Soil_Moisture;
int Pump_Status;
int Pump_pin = 16;

void setup() {
  pinMode(Pump_pin,OUTPUT);
  Serial.begin(115200);  // Initialize serial
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  
  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }
  int sm = analogRead(A0);

  Soil_Moisture = map(sm , 0 , 1023 , 100 , 0);
  if (Soil_Moisture < 20){
    digitalWrite(Pump_pin,LOW);
    Pump_Status = 1;
  }
  else if (Soil_Moisture > 50){
    digitalWrite(Pump_pin,HIGH);
    Pump_Status = 0;
  }


  // set the fields with the values
  ThingSpeak.setField(1, Soil_Moisture);
  ThingSpeak.setField(2, Pump_Status);

  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  
 
  delay(15000); // Wait 20 seconds to update the channel again
}
