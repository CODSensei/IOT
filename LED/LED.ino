



/*************************************************************


 This sketch shows how to read values from Virtual Pins


 App dashboard setup:
   Slider widget (0...100) on Virtual Pin V1
*************************************************************/


/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL3dC-ihCku"
#define BLYNK_TEMPLATE_NAME "project Manhattan"
#define BLYNK_AUTH_TOKEN "lJXO2lCfuiyZnrdkTaAC9QQKKEobrmsa"
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial




#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "MKS";
char pass[] = "Nahi_dena";


// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin V1
BLYNK_WRITE(V0)
{
 int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable


// digitalWrite(pin no. , pinValue) // not recommended


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
BLYNK_WRITE(V1)
{
 int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable


// digitalWrite(pin no. , pinValue) // not recommended


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




void setup()
{
 pinMode(16,OUTPUT); // Telling the pin to act as output pin
 pinMode(2,OUTPUT);
 // Debug console
 Serial.begin(115200);


 Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
 // You can also specify server:
 //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
 //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);
}


void loop()
{
 Blynk.run();
}












