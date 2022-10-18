
#include <WiFiNINA.h>
#include <MQTT.h>
#include "wifiCredentials.h"

#define POT_PIN A0
const char ssid[] = WIFI_SSID;
const char pass[] = WIFI_PASS;

int potValue;
int prevPotValue = 0;

WiFiClient net;
MQTTClient client;
int status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(115200);
  pinMode(POT_PIN, OUTPUT);  

  // attempt to connect to Wifi network:
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print("No WiFi connection");
    delay(5000);
  }
  
  // once you are connected :
  Serial.println("You're connected to the network");

  //start mqtt
  client.begin("physical-computing-zhdk.cloud.shiftr.io", net);
  connect();
}

void loop() {
  client.loop();
  delay(10);

  // check if connected
  if (!client.connected()) {
    connect();
  }

  potValue = analogRead(POT_PIN);
  potValueMapped= map(potValue, 0, 1023, 0, 255);
  Serial.print("Potentiometer: "); Serial.println(potValueMapped);

   //send current value only if different from previous value
   if (potValueMapped !=prevPotValue){
    client.publish("/ledValue", String(potValueMapped));
    prevPotValue = potValueMapped;
  } 

}

void connect() {
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("No Wifi connection...");
    delay(1000);
  }

  while (!client.connect("sender", "physical-computing-zhdk", "QO1d1kxcIhqD2pi2")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected to MQTT!");
}