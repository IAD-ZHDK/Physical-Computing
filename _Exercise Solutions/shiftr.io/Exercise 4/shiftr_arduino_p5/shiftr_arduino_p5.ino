
#include <WiFiNINA.h>
#include <MQTT.h>
#include "wifiCredentials.h"
#define ledPin 10

const char ssid[] = WIFI_SSID;
const char pass[] = WIFI_PASS;
WiFiClient net;
MQTTClient client;
int status = WL_IDLE_STATUS;  

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  // attempt to connect to Wifi network:
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print("No WiFi connection");
    delay(5000);
  }
  
  // once you are connected :
  Serial.println("You're connected to the network");

  //start mqtt
  //change this to match your instance name
  client.begin("physical-computing-zhdk.cloud.shiftr.io", net);
  client.onMessage(messageReceived);
  connect();
}

void loop() {
  client.loop();
  delay(10);

  // check if connected
  if (!client.connected()) {
    connect();
  }
}

void messageReceived(String &topic, String &payload) {
  Serial.println(topic + ": " + payload);
  analogWrite(ledPin, payload.toInt());
}

void connect() {
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("No Wifi connection...");
    delay(1000);
  }

  //change this to match your instance
  while (!client.connect("arduino", "physical-computing-zhdk", "QO1d1kxcIhqD2pi2")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected to MQTT!")
  client.subscribe("sliderValue");
}


  

