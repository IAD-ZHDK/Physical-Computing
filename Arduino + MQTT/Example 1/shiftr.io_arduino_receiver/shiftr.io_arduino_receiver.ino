
#include <WiFiNINA.h>
#include <MQTT.h>
#include "wifiCredentials.h"

const char ssid[] = WIFI_SSID;
const char pass[] = WIFI_PASS;
unsigned long lastMillis = 0;
int ledBlink; 

WiFiClient net;
MQTTClient client;
int status = WL_IDLE_STATUS;  

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  // attempt to connect to Wifi network:
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print("No WiFi connection");
    delay(5000);
  }
  
  // once you are connected :
  Serial.println("You're connected to the network");

  //start mqtt
  //the first argument is the name of your instance on shiftr
  //the second argument should be set to net
  client.begin("physical-computing-zhdk.cloud.shiftr.io", net);
  //print message once is received
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
//this is a callback function if a topic we subscribed sends a message
//payload is the received message 
void messageReceived(String &topic, String &payload) {
  Serial.println(topic + ": " + payload);
  //Since the received data is formatted as String we need to convert it back to a number
  digitalWrite(LED_BUILTIN, payload.toInt());
}

void connect() {
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("No Wifi connection...");
    delay(1000);
  }
  //first argument is your ID
  //second argument is the username of your shiftr.io instance as found in token settings
  //third argument is your secret token which can be set in your instance settings
  while (!client.connect("receiver", "physical-computing-zhdk", "QO1d1kxcIhqD2pi2")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected to MQTT!");
  //subscribe to message from the topic "ledBlink" 
  client.subscribe("ledBlink");
}