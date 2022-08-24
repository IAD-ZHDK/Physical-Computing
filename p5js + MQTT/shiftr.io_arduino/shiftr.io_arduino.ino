
#include <WiFiNINA.h>
#include <MQTT.h>
#include "wifiCredentials.h"

const char ssid[] = WIFI_SSID;
const char pass[] = WIFI_PASS;
char cstr[16];
float xPos = 0;
float yPos = 0;

WiFiClient net;
MQTTClient client;
int status = WL_IDLE_STATUS;  

unsigned long lastMillis = 0;

void connect() {

  while (!client.connect("", "", "")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("You're connected to the MQTT broker!");
  client.subscribe("ledBlink");
}

void messageReceived(String &topic, String &payload) {
  Serial.println(topic + ": " + payload);
  int blinkVal = constrain(payload.toInt(), 0, 1);
  digitalWrite(LED_BUILTIN, blinkVal);
  
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  // attempt to connect to Wifi network:
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }
  
  // once you are connected :
  Serial.println("You're connected to the network");


  //start mqtt
  client.begin("", net);
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

  // publish a message roughly every second.
  if (millis() - lastMillis > 1000) {
    lastMillis = millis();
    client.publish("/pos", "{\"x\":" + String(xPos)+ ",\"y\":" + String(yPos) + "}");
    
    xPos += 1;
    yPos += 2;
  }

  
}
