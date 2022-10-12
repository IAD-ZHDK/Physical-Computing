// Aruindo Master Sketch

#include <Wire.h>

byte recI2C;               // data received from I2C bus
unsigned long time_start;   // start time in milliseconds
int ledVal;               // status of LED: 1 = ON, 0 = OFF
byte potVal;             // potentiometer position

void setup(){
  Wire.begin(); // join I2C bus as the master
  
  // initialize global variables
  recI2C = 255;
  time_start = millis();
  ledVal = 0;
  
  pinMode(10, OUTPUT);    // set pin 13 as an output
  Serial.begin(9600);
}

void loop(){
  // read potentiometer position
  potVal = analogRead(A0);   // read the voltage at pin A0 (potentiometer voltage)

  // send potentiometer position to Slave device 0x08
  Wire.beginTransmission(0x08); // informs the bus that we will be sending data to slave device 8 (0x08)
  Wire.write(potVal);        // send value_pot
  Wire.endTransmission();       // informs the bus and the slave device that we have finished sending data

  Wire.requestFrom(0x08, 1);    // request potentiometer position from slave 0x08
  if(Wire.available()) {        // read response from slave 0x08
    recI2C = Wire.read();
  }
  
  // blink logic code
//  if((millis() - time_start) > (1000 * (float)(recI2C/255))) {
//    ledVal = !ledVal;
//    time_start = millis();
//  }
//  
  ledVal = (int)(recI2C/255); //normalizing the incoming data between 0 and 1
  digitalWrite(10, ledVal);
  Serial.println(ledVal);
}
