
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
  connect();
}

void loop() {
  client.loop();
  delay(10);

  // check if connected
  if (!client.connected()) {
    connect();
  }

  // publish a message roughly every 1 seconds.
  if (millis() - lastMillis > 1000) {
    lastMillis = millis();
  
    if(ledBlink == 1) {
      ledBlink = 0;
    }else {
      ledBlink = 1;
    }

    //here we need to make sure that we publish (send) a message to a topic
    //in this case it's called "ledBlink". You need to make sure that your
    //topic always starts with a "/"
    //the second argument is your message (payload) which needs to be send out as string
    client.publish("/ledBlink", String(ledBlink));
  }

}


void connect() {
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("No Wifi connection...");
    delay(1000);
  }
//first argument is your ID
  //second argument is the username of your shiftr.io instance as found in token settings
  //third argument is your secret token which can be set in your instance settings
  while (!client.connect("sender", "physical-computing-zhdk", "QO1d1kxcIhqD2pi2")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected to MQTT!");
  
}