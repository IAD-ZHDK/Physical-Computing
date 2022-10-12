
const int sensorPin = A0;  
const int DELAY_MS = 200;

// variables:
int sensorValue = 0;         // the sensor value
int sensorMin = 1023;        // minimum sensor value
int sensorMax = 0;           // maximum sensor value


void setup() {
  Serial.begin(9600);

   // calibrate during the first five seconds
   
   while (millis() < 5000) {
    sensorValue = analogRead(sensorPin);
    
    // record the maximum sensor value
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }
    // record the minimum sensor value
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }
    // delay a bit
    delay(50);
  }
}

void loop() {

   // read the sensor:
  sensorValue = analogRead(sensorPin);
  // apply the calibration to the sensor reading
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 1);
  // in case the sensor value is outside the range seen during calibration
  sensorValue = constrain(sensorValue, 0, 1);
  delay(DELAY_MS);
  Serial.println(sensorValue);  
 
}
