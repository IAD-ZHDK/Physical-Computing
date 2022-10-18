#include <Servo.h>

#define OUTPUT_PIN 11
const int DELAY_MS = 20;
int inputVal; 

Servo myservo;

int value = 0;

void setup() {
  Serial.begin(9600);
  myservo.attach(11);
}

void loop() {
  // Check to see if there is any incoming serial data
  Serial.print("Data received:");
  if (Serial.available() > 0) {
    // read string until the endo of the line
    String rcvdSerialData = Serial.readStringUntil('\n');
     
      value = rcvdSerialData.toInt();
      //this will be seen in the console
      Serial.print("Data received:" + rcvdSerialData);
      myservo.write(value);
    
    //analogWrite(OUTPUT_PIN, value);
    delay(DELAY_MS);
  }
}
