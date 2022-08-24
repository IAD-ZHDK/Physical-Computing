#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int angle = 160;  // goal angle of servo
float easedAngle;  // for storing an eased position between current and goal angle
int lastChange;    // Used for timing changes of angle

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  Serial.begin(9600);
}

void loop() {
  // change the goal angle every 5000 miliseconds
  if (millis()>= lastChange+5000) {
    lastChange = millis();
    if (angle == 160) {
      angle = 20;
    } else {
      angle = 160;
    }
  }
  
  
  easedAngle = angle*0.02 + easedAngle*0.98;

  
  Serial.print(angle);
  Serial.print(",");
  Serial.println(int(easedAngle)); 
  myservo.write(easedAngle);   
  delay(10);
}
