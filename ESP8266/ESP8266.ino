#include <MQ135.h>
#define THINGER_SERIAL_DEBUG

#include <ThingerESP8266.h>
#include "arduino_secrets.h"

#define PIN_MQ135 A0

MQ135 mq135_sensor(PIN_MQ135);
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);
void setup() {
  // open serial for monitoring
  Serial.begin(115200);

  // set builtin led as output
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(16, OUTPUT);

  // add WiFi credentials
  thing.add_wifi(SSID, SSID_PASSWORD);

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  thing["led1"] << digitalPin(LED_BUILTIN);
  thing["led2"] << digitalPin(16);

  // resource output example (i.e. reading a sensor value)
  thing["MQ135"] >> [] (pson &out){
    out["AQI"] = mq135_sensor.getPPM();
  };

  // more details at http://docs.thinger.io/arduino/
}

void loop() {
  thing.handle();
}