
#include <WiFiNINA.h>
#include <MQTT.h>
#include "wifiCredentials.h"
#define POT_PIN A0

const char ssid[] = WIFI_SSID;
const char pass[] = WIFI_PASS;
int xPos = 100;
int yPos = 100;
int diameter = 0;
int potValue = 0;
int prevPotValue = 0;
int potMapped = 0;

WiFiClient net;
MQTTClient client;
int status = WL_IDLE_STATUS;  

unsigned long lastMillis = 0;

void setup() {
  Serial.begin(115200);
  pinMode(POT_PIN, INPUT);
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

  potValue = analogRead(POT_PIN);
  potMapped = map(potValue, 0, 1023, 0, 300);

 //publish only if value is different from previous value
  if (potMapped != prevPotValue){
    client.publish("/diameter", "diameter," + String(potMapped));
  }

  prevPotValue = potMapped;
  

  // publish a message roughly every second.
  if (millis() - lastMillis > 1000) {
    lastMillis = millis();

    //make sure you add comma after the string e.x. posX, 
    client.publish("/posX", "posX," + String(xPos));
    client.publish("/posY", "posY," + String(yPos));
   
    //you can also send the message formatted as json
    //client.publish("/pos", "{\"x\":" + String(xPos)+ ",\"y\":" + String(yPos) + "}");
    
    if (xPos < 500){
        xPos += 10;
        yPos += 5;
    } else {
        xPos = 100;
        yPos = 100;
    }
  }
}

void messageReceived(String &topic, String &payload) {
  Serial.println(topic + ": " + payload);
  int blinkVal = constrain(payload.toInt(), 0, 1);
  digitalWrite(LED_BUILTIN, blinkVal);
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

  Serial.println("\nconnected to MQTT!");
}


  

